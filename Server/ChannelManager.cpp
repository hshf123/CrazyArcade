#include "pch.h"
#include "ChannelManager.h"
#include "Channel.h"
#include "Player.h"

void ChannelManager::Update()
{
	WRITE_LOCK;
	for (auto& p : _channels)
	{
		p.second->Update();
	}
}

void ChannelManager::AddChannel(int32 maxPlayerCount /*= 20*/)
{
	WRITE_LOCK;
	ChannelRef channel = MakeShared<Channel>();
	channel->ChannelInfo.set_channelid(_increaseId);
	channel->ChannelInfo.set_maxplayercount(maxPlayerCount);
	channel->ChannelInfo.set_currentplayercount(0);
	_channels.insert({ _increaseId++, channel });
}

void ChannelManager::RemoveChannel(int64 channelId)
{
	WRITE_LOCK;
	_channels.erase(channelId);
}

ChannelRef ChannelManager::FindChannel(int64 channelId)
{
	READ_LOCK;
	auto findIt = _channels.find(channelId);
	if (findIt == _channels.end())
		return nullptr;

	return findIt->second;
}

void ChannelManager::AddPlayer(PlayerRef player)
{
	WRITE_LOCK;
	_players.insert({ player->PlayerInfo.id(), player });
}

void ChannelManager::RemovePlayer(int64 playerId)
{
	WRITE_LOCK;
	_players.erase(playerId);
}

PlayerRef ChannelManager::FindPlayer(int64 playerId)
{
	READ_LOCK;
	auto findIt = _players.find(playerId);
	if (findIt == _players.end())
		return nullptr;

	return findIt->second;
}

Vector<Protocol::PChannel> ChannelManager::GetChannelsProtocol()
{
	Vector<Protocol::PChannel> res;
	READ_LOCK;
	for (auto& p : _channels)
	{
		res.push_back(*p.second->GetChannelProtocol());
	}
	return res;
}