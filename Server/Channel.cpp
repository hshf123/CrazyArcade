#include "pch.h"
#include "Channel.h"
#include "Player.h"
#include "Room.h"

Channel::Channel(int64 id, int32 maxPlayerCount)
	: _id(id), _maxPlayerCount(maxPlayerCount), _currentPlayerCount(0)
{

}

void Channel::AddRoom(int32 maxPlayerCount /*= 8*/)
{
	WRITE_LOCK;
	// TODO : increaseId Á¶Àý
	RoomRef room = MakeShared<Room>(_increaseId, maxPlayerCount);
	_rooms.insert({ _increaseId++, room });
}

void Channel::RemoveRoom(int32 roomId)
{
	WRITE_LOCK;
	_rooms.erase(roomId);
}

RoomRef Channel::FindRoom(int32 roomId)
{
	READ_LOCK;
	auto findIt = _rooms.find(roomId);
	if (findIt == _rooms.end())
		return nullptr;

	return findIt->second;
}

void Channel::InsertPlayer(PlayerRef player)
{
	WRITE_LOCK;
	_players.insert({ player->GetId(), player });
}

void Channel::RemovePlayer(int64 playerId)
{
	WRITE_LOCK;
	_players.erase(playerId);
}

PlayerRef Channel::FindPlayer(int64 playerId)
{
	READ_LOCK;
	auto findIt = _players.find(playerId);
	if (findIt == _players.end())
		return nullptr;

	return findIt->second;
}

void Channel::FillChannelInfo(Protocol::Channel* pkt)
{
	pkt->set_channelid(_id);
	pkt->set_maxplayercount(_maxPlayerCount);
	pkt->set_currentplayercount(_currentPlayerCount);
}

void Channel::FillRoomInfo(Protocol::RoomInfo* pkt)
{
	READ_LOCK;
	pkt->set_roomcount(_rooms.size());
	for (auto p : _rooms)
	{
		Protocol::Room* room = pkt->add_rooms();
		p.second->FillRoomlInfo(room);
	}
}

void Channel::Broadcast(SendBufferRef sendBuffer)
{
	READ_LOCK;
	for (auto& p : _players)
	{
		p.second->Send(sendBuffer);
	}
}
