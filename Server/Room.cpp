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

		if (p.second->PlayerInfo.ready() == false)
			return false;
	}

	// TODO 방에있는 모두에게 기본 PositioniInfo 채워주기

	Protocol::S_ROOMSTART roomStartPkt;
	roomStartPkt.set_success(true);
	roomStartPkt.set_allocated_room(GetRoomProtocol());
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(roomStartPkt);
	Broadcast(sendBuffer);

	_state = RoomState::GAMESTART;

	// TODO 채널에 있는 사람들한테 게임 시작중인방이라고 broadcast

	return true;
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
