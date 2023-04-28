#include "pch.h"
#include "Room.h"
#include "Player.h"
#include "Protocol.pb.h"
#include "ForestMap.h"
#include "ThreadManager.h"
#include "Channel.h"

Room::Room(int64 id, const string& roomName, int32 maxPlayerCount)
	:_roomId(id), _maxPlayerCount(maxPlayerCount)
{
	_roomName = Utils::ConvertStringToWString(roomName);
}

void Room::InsertPlayer(PlayerRef player)
{
	WRITE_LOCK;
	_players.insert({ player->PlayerInfo.id(), player});
	_currentPlayerCount++;
	SetIdx(player);
	player->PlayerInfo.set_roomid(_roomId);
	player->SetRoom(shared_from_this());
}

void Room::RemovePlayer(int64 playerId)
{
	PlayerRef player = FindPlayer(playerId);
	if (player == nullptr)
		return;

	if (player == GetLeader())
	{
		Vector<PlayerRef> players;
		{
			WRITE_LOCK;
			for(auto& p : _players)
			{
				p.second->PlayerInfo.set_roomid(-1);
				p.second->SetRoom(nullptr);
				_currentPlayerCount--;
				players.push_back(p.second);
			}
			_players.clear();
			_idxes.clear();
		}

		ChannelRef channel = GetChannel();
		channel->RemoveRoom(_roomId);
		for(auto& p : players)
		{
			channel->InsertPlayer(p);
		}

		wstringstream log;
		log << L"PLAYER ID : " << player->PlayerInfo.id() << L" LEAVE ROOM ID : " << _roomId;
		Utils::Log(log);

		return;
	}
	{
		WRITE_LOCK;
		player->PlayerInfo.set_roomid(-1);
		player->SetRoom(nullptr);
		_players.erase(playerId);
		_idxes.erase(player->PlayerInfo.roomidx());
		_currentPlayerCount--;
	}

	_channel->InsertPlayer(player);

	Protocol::S_ROOMUPDATE roomUpdatePkt;
	roomUpdatePkt.set_allocated_room(GetRoomProtocol());
	Broadcast(roomUpdatePkt, player->GetClientSession());

	wstringstream log;
	log << L"PLAYER ID : " << player->PlayerInfo.id() << L" LEAVE ROOM ID : " << _roomId;
	Utils::Log(log);
}

PlayerRef Room::FindPlayer(int64 playerId)
{
	READ_LOCK;
	auto findIt = _players.find(playerId);
	if (findIt == _players.end())
		return nullptr;

	return findIt->second;
}

void Room::SetIdx(PlayerRef player)
{
	for (int i = 0; i < 8; i++)
	{
		if (_idxes[i] == nullptr && _benList[i] == false)
		{
			_idxes[i] = player;
			player->PlayerInfo.set_roomidx(i);
			return;
		}
	}
}

void Room::PlayerDead(PlayerRef player)
{
	if (player == nullptr)
	{
		wstringstream log;
		log << L"PLYAERDEAD FUNC ERROR PLYAER IS NULLPTR";
		Utils::Log(log);
		return;
	}

	player->OnDead();
	_forestMap->ApplyLeave(player);
	_forestMap->PlayerCount--;
	player->Rank = _rank--;

	if (_forestMap->PlayerCount == 1)
	{
		// TODO : 게임 결과 보여주기
		Protocol::S_GAMEEND gameEndPkt;
		for (auto& p : _players)
		{
			Protocol::PRoomEnd* roomEnd = gameEndPkt.add_endinfo();
			roomEnd->set_rank(player->Rank);
			roomEnd->set_allocated_player(p.second->GetPlayerProtocol());
		}
		Broadcast(gameEndPkt);
	}
}

bool Room::CanGameStart()
{
	GameInit();
	{
		WRITE_LOCK;
		if (_currentPlayerCount < 2)
			return false;

		for (auto& p : _players)
		{
			if (p.second->PlayerInfo.id() == _leaderId)
				continue;

			// 게임 시작 못하면 로그 남기기
			if (p.second->PlayerInfo.ready() == false)
				return false;
		}

		Protocol::S_ROOMSTART roomStartPkt;
		roomStartPkt.set_success(true);
		roomStartPkt.set_allocated_room(GetRoomProtocol());

		int32 idx = 0;
		for (auto& p : _players)
		{
			// 모든 플레이어의 기본 PosInfo 초기화 후 Broadcast
			if (p.second == nullptr)
			{
				// TODO 연결 끊긴건지 확인 후 제외하고 플레이
				return false;
			}
			Protocol::PPositionInfo* basicPosInfo = GetBasicPosInfo(idx++);
			p.second->PosInfo.CopyFrom(*basicPosInfo);
			Protocol::PRoomStart* roomStart = roomStartPkt.add_spawn();
			roomStart->set_allocated_playerinfo(p.second->GetPlayerProtocol());
			roomStart->set_allocated_posinfo(p.second->GetPositionInfoProtocol());

			_forestMap->ApplyMove(p.second, p.second->GetCellPos());
		}

		Broadcast(roomStartPkt);

		_state = RoomState::GAMESTART;
	}
	// TODO 채널에 있는 사람들한테 게임 시작중인방이라고 broadcast
	return true;
}

void Room::GameInit()
{
	WRITE_LOCK;
	_forestMap = MakeShared<ForestMap>();
	_forestMap->LoadMap();
	_forestMap->OwnerRoom = shared_from_this();
	_forestMap->PlayerCount = _currentPlayerCount;
	for (auto& p : _players)
	{
		p.second->Kill = 0;
	}
	_rank = _players.size();
}

Protocol::PPositionInfo* Room::GetBasicPosInfo(int32 idx)
{
	Protocol::PPositionInfo* pkt = new Protocol::PPositionInfo();
	pkt->set_state(Protocol::PPlayerState::IDLE);
	pkt->set_movedir(Protocol::PMoveDir::DOWN);
	int32 posx = _respawnPosX[idx];
	int32 posy = _respawnPosY[idx];
	Protocol::PWorldPos* worldPos = new Protocol::PWorldPos();
	worldPos->set_posx(posx + 0.5f);
	worldPos->set_posy(posy + 0.5f);
	pkt->set_allocated_worldpos(worldPos);
	Protocol::PCellPos* cellPos = new Protocol::PCellPos();
	cellPos->set_posx(posx);
	cellPos->set_posy(posy);
	pkt->set_allocated_cellpos(cellPos);
	return pkt;
}

void Room::CopyRoomProtocol(Protocol::PRoom* pkt)
{
	READ_LOCK;
	pkt->set_roomid(_roomId);
	pkt->set_roomname(GetRoomName());
	pkt->set_leaderid(_leaderId);
	pkt->set_maxplayercount(_maxPlayerCount);
	pkt->set_currentplayercount(_currentPlayerCount);
}

Protocol::PRoom* Room::GetRoomProtocol()
{
	Protocol::PRoom* pkt = new Protocol::PRoom();
	pkt->set_roomid(_roomId);
	pkt->set_roomname(GetRoomName());
	pkt->set_leaderid(_leaderId);
	pkt->set_maxplayercount(_maxPlayerCount);
	pkt->set_currentplayercount(_currentPlayerCount);

	for (int i = 0; i < 8; i++)
		pkt->add_benlist(_benList[i]);
	for (auto& p : _players)
	{
		Protocol::PPlayer* player = pkt->add_playerlist();
		p.second->CopyPlayerProtocol(player);
	}
	return pkt;
}

void Room::SetLeader(int64 playerId)
{
	WRITE_LOCK;
	_leaderId = playerId;
}

void Room::Broadcast(SendBufferRef sendBuffer, ClientSessionRef exceptSession /*= nullptr*/)
{
	READ_LOCK;
	for (auto& p : _players)
	{
		if (exceptSession != nullptr && p.second->GetClientSession() == exceptSession)
			continue;
		p.second->Send(sendBuffer);
	}
}

void Room::HandleChat(PlayerRef player, Protocol::C_ROOMCHAT& pkt)
{
	Protocol::S_ROOMCHAT roomChatPkt;
	roomChatPkt.set_allocated_player(player->GetPlayerProtocol());
	roomChatPkt.set_msg(pkt.msg());
	Broadcast(roomChatPkt);
}

void Room::HandleMove(PlayerRef player, Protocol::C_MOVE& pkt)
{
	if (player == nullptr)
		return;

	WRITE_LOCK;
	_forestMap->ApplyMove(player, player->GetCellPos());
	player->PosInfo = pkt.positioninfo();

	// 다른 플레이어한테도 알려준다
	Protocol::S_MOVE movePkt;
	movePkt.set_allocated_player(player->GetPlayerProtocol());
	movePkt.set_allocated_positioninfo(player->GetPositionInfoProtocol());
	Broadcast(movePkt);
}

void Room::HandleBomb(PlayerRef player, Protocol::C_BOMB& pkt)
{
	if (player == nullptr)
		return;
	
	WRITE_LOCK;
	Vector2 bombPos = player->GetWorldPos() + Vector2(0, -0.3f);
	Vector2Int bombCellPos = _forestMap->WorldToCell(bombPos);

	if (_forestMap->SetBomb(bombCellPos, player) == false)
		return;

	{
		wstringstream log;
		log << L"Player ID : " << player->PlayerInfo.id();
		log << L" has placed a Bomb at (" << bombCellPos.x << ", " << bombCellPos.y << ")";
		Utils::Log(log);
	}

	Protocol::S_BOMB bombPkt;
	bombPkt.set_allocated_player(player->GetPlayerProtocol());
	bombPkt.set_allocated_cellpos(_forestMap->GetCellPosProtocol(bombCellPos));
	Broadcast(bombPkt);
}

void Room::HandleBombEnd(PlayerRef player, Protocol::C_BOMBEND& pkt)
{
	WRITE_LOCK;
	Vector2Int bombCellPos = Vector2Int(pkt.cellpos().posx(), pkt.cellpos().posy());

	Protocol::S_BOMBEND bombEndPkt;
	bombEndPkt.set_allocated_player(player->GetPlayerProtocol());
	_forestMap->DestroyBomb(bombCellPos, player->PlayerInfo.bombrange(), bombEndPkt);
	_forestMap->BombResult(bombEndPkt);
	player->SubBomb();
	Broadcast(bombEndPkt);

	wstringstream log;
	log << L"Player ID : " << player->PlayerInfo.id();
	log << L" A bomb located at (" << bombCellPos.x << ", " << bombCellPos.y << ")" << L" exploded.";
	Utils::Log(log);
}