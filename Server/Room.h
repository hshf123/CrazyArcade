#pragma once

class Room
{
public:
	Room(int64 id, const string& roomName, int32 maxPlayerCount);

	void InsertPlayer(PlayerRef player);
	void RemovePlayer(int64 playerId);
	PlayerRef FindPlayer(int64 playerId);
	void SetIdx(PlayerRef player);

	void CopyRoomProtocol(Protocol::Room* pkt);
	Protocol::Room* GetRoomProtocol();
	Protocol::RoomInfo* GetRoomInfoProtocol();

public:
	int32 GetId() { return _roomId; }
	string GetRoomName() { return Utils::ConvertWStringToString(_roomName); }
	void SetLeader(int64 playerId);
	PlayerRef GetLeader() { return FindPlayer(_leaderId); }

	void Broadcast(SendBufferRef sendBuffer);

private:
	USE_LOCK;
	HashMap<int64, PlayerRef> _players;
	HashMap<int32, PlayerRef> _idxes;

private:
	int32 _roomId;
	wstring _roomName;
	int32 _maxPlayerCount = 0;
	int32 _currentPlayerCount = 0;

	int64 _leaderId;
	bool _benList[8];
};

