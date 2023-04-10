#pragma once

using RoomRef = shared_ptr<class Room>; 

// RoomManager °â¿ë
class Channel
{
public:
	Channel(int64 id, int32 maxPlayerCount);

	// void AddRoom();
	// void RemoveRoom();
	// RoomRef FindRoom();

	void InsertPlayer(PlayerRef player);
	void RemovePlayer(int64 playerId);
	PlayerRef FindPlayer(int64 playerId);

	void FillChannelInfo(Protocol::Channel* pkt);

private:
	USE_LOCK;
	HashMap<int64, RoomRef> _rooms;
	HashMap<int64, PlayerRef> _players;

private:
	int64 _id;
	int32 _maxPlayerCount = 0;
	int32 _currentPlayerCount = 0;
};
