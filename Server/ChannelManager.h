#pragma once

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
	void Update();

	void AddChannel(int32 maxPlayerCount = 20);
	void RemoveChannel(int64 channelId);
	ChannelRef FindChannel(int64 channelId);

	void AddPlayer(PlayerRef player);
	void RemovePlayer(int64 playerId);
	PlayerRef FindPlayer(int64 playerId);

	Vector<Protocol::PChannel> GetChannelsProtocol();

private:
	USE_LOCK;
	HashMap<int64, ChannelRef> _channels;
	HashMap<int64, PlayerRef> _players; // 채널 선택중인 유저정보
	int64 _increaseId = 1;
};
