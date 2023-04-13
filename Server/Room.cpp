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
}

void Room::RemovePlayer(int64 playerId)
{
	WRITE_LOCK;
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

void Room::FillRoomlInfo(Protocol::Room* pkt)
{
	pkt->set_roomid(_roomId);
	pkt->set_maxplayercount(_maxPlayerCount);
	pkt->set_currentplayercount(_currentPlayerCount);
}

void Room::SetLeader(int64 playerId)
{
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
