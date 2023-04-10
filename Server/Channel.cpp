#include "pch.h"
#include "Channel.h"
#include "Player.h"

Channel::Channel(int64 id, int32 maxPlayerCount)
	: _id(id), _maxPlayerCount(maxPlayerCount), _currentPlayerCount(0)
{

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
	WRITE_LOCK;
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
