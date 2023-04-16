#include "pch.h"
#include "Room.h"
#include "Player.h"
#include "ClientPacketHandler.h"

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
}

void Room::RemovePlayer(int64 playerId)
{
	WRITE_LOCK;
	PlayerRef player = FindPlayer(playerId);
	if (player == nullptr)
		return;
	_idxes.erase(player->PlayerInfo.roomidx());
	_players.erase(playerId);
	_currentPlayerCount--;
	_idxes[player->PlayerInfo.roomidx()] = nullptr;
	player->PlayerInfo.set_roomid(-1);
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

bool Room::CanGameStart()
{
	READ_LOCK;

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
		auto basicPosInfo = GetBasicPosInfo(idx++);
		p.second->PosInfo.CopyFrom(*basicPosInfo);
		Protocol::PRoomStart* roomStart = roomStartPkt.add_spawn();
		roomStart->set_allocated_playerinfo(p.second->GetPlayerProtocol());
		roomStart->set_allocated_posinfo(p.second->GetPositionInfoProtocol());
	}

	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(roomStartPkt);
	Broadcast(sendBuffer);

	_state = RoomState::GAMESTART;

	// TODO 채널에 있는 사람들한테 게임 시작중인방이라고 broadcast

	return true;
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
	READ_LOCK;
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
