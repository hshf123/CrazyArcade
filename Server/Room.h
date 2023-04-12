#pragma once

class Room
{
public:
	Room(int64 id, int32 maxPlayerCount);

	void InsertPlayer(PlayerRef player);
	void RemovePlayer(int64 playerId);
	PlayerRef FindPlayer(int64 playerId);

	void FillRoomlInfo(Protocol::Room* pkt);

private:
	USE_LOCK;
	HashMap<int64, PlayerRef> _players;

private:
	int64 _id;
	wstring _roomName;
	int32 _maxPlayerCount = 0;
	int32 _currentPlayerCount = 0;
};

