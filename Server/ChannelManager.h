#pragma once

using ChannelRef = shared_ptr<class Channel>;

class ChannelManager
{
private:
	ChannelManager() { }
	~ChannelManager() { }

public:
	static ChannelManager* GetInstance()
	{
		static ChannelManager instance;
		return &instance;
	}

public:
	void AddChannel(int32 maxPlayerCount = 500);
	void RemoveChannel(int64 channelId);
	ChannelRef FindChannel(int64 channelId);

	void FillChannelInfo(Protocol::ChannelInfo* channelInfo);

private:
	USE_LOCK;
	HashMap<int64, ChannelRef> _channels;
	int64 _id = 1;
};

