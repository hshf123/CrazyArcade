#include "pch.h"
#include "ChannelManager.h"
#include "Channel.h"
#include "Player.h"

void ChannelManager::AddChannel(int32 maxPlayerCount /*= 500*/)
{
	WRITE_LOCK;
	ChannelRef channel = MakeShared<Channel>(_increaseId, maxPlayerCount);
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
	_players.insert({ player->GetId(), player });
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

Protocol::ChannelInfo* ChannelManager::GetChannelInfoProtocol()
{
	Protocol::ChannelInfo* pkt = new Protocol::ChannelInfo();
	READ_LOCK;
	pkt->set_channelcount(_channels.size());
	for (auto& p : _channels)
	{
		Protocol::Channel* c = pkt->add_channels();
		p.second->CopyChannelProtocol(c);
	}
	return pkt;
}
