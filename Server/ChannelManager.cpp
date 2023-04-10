#include "pch.h"
#include "ChannelManager.h"
#include "Channel.h"

void ChannelManager::AddChannel(int32 maxPlayerCount /*= 500*/)
{
	WRITE_LOCK;
	ChannelRef channel = MakeShared<Channel>(_id, maxPlayerCount);
	_channels.insert({ _id++, channel });
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

void ChannelManager::FillChannelInfo(Protocol::ChannelInfo* channelInfo)
{
	READ_LOCK;
	channelInfo->set_channelcount(_channels.size());
	for (auto& p : _channels)
	{
		Protocol::Channel* c = channelInfo->add_channels();
		p.second->FillChannelInfo(c);
	}
}
