#include "pch.h"
#include "Room.h"
#include "Player.h"

Room::Room(int64 id, int32 maxPlayerCount)
	:_id(id), _maxPlayerCount(maxPlayerCount)
{

}

void Room::InsertPlayer(PlayerRef player)
{
	WRITE_LOCK;
	_players.insert({ player->GetId(), player });
}

void Room::RemovePlayer(int64 playerId)
{
	WRITE_LOCK;
	_players.erase(playerId);
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
	pkt->set_roomid(_id);
	pkt->set_maxplayercount(_maxPlayerCount);
	pkt->set_currentplayercount(_currentPlayerCount);
}

void Room::Broadcast(SendBufferRef sendBuffer)
{
	READ_LOCK;
	for (auto& p : _players)
	{
		p.second->Send(sendBuffer);
	}
}
