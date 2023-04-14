#include "pch.h"
#include "Room.h"
#include "Player.h"

Room::Room(int64 id, const string& roomName, int32 maxPlayerCount)
	:_roomId(id), _maxPlayerCount(maxPlayerCount)
{
	_roomName = Utils::ConvertStringToWString(roomName);
}

void Room::InsertPlayer(PlayerRef player)
{
	WRITE_LOCK;
	_players.insert({ player->GetId(), player });
	_currentPlayerCount++;
	SetIdx(player);
}

void Room::RemovePlayer(int64 playerId)
{
	WRITE_LOCK;
	_idxes.erase(FindPlayer(playerId)->GetRoomIdx());
	_players.erase(playerId);
	_currentPlayerCount--;
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
			player->SetRoomIdx(i);
			return;
		}
	}
}

void Room::CopyRoomProtocol(Protocol::Room* pkt)
{
	READ_LOCK;
	pkt->set_roomid(_roomId);
	pkt->set_roomname(GetRoomName());
	pkt->set_leaderid(_leaderId);
	pkt->set_maxplayercount(_maxPlayerCount);
	pkt->set_currentplayercount(_currentPlayerCount);
}

Protocol::Room* Room::GetRoomProtocol()
{
	Protocol::Room* pkt = new Protocol::Room();
	READ_LOCK;
	pkt->set_roomid(_roomId);
	pkt->set_roomname(GetRoomName());
	pkt->set_leaderid(_leaderId);
	pkt->set_maxplayercount(_maxPlayerCount);
	pkt->set_currentplayercount(_currentPlayerCount);
	return pkt;
}

Protocol::RoomInfo* Room::GetRoomInfoProtocol()
{
	Protocol::RoomInfo* pkt = new Protocol::RoomInfo();
	READ_LOCK;
	pkt->set_roomid(_roomId);
	pkt->set_allocated_room(GetRoomProtocol());
	for (int i = 0; i < 8; i++)
		pkt->add_benlist(_benList[i]);
	for (auto& p : _players)
	{
		Protocol::Player* player = pkt->add_playerlist();
		p.second->CopyPlayerProtocol(player);
	}
	return pkt;
}

void Room::SetLeader(int64 playerId)
{
	WRITE_LOCK;
	_leaderId = playerId;
}

void Room::Broadcast(SendBufferRef sendBuffer)
{
	READ_LOCK;
	for (auto& p : _players)
	{
		p.second->Send(sendBuffer);
	}
}
