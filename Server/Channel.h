#pragma once

using RoomRef = shared_ptr<class Room>; 

// RoomManager °â¿ë
class Channel
{
public:
	Channel(int64 id, int32 maxPlayerCount);

	void AddRoom(int64 playerId, const string& roomName, int32 maxPlayerCount = 8);
	void RemoveRoom(int32 roomId);
	RoomRef FindRoom(int32 roomId);

	void InsertPlayer(PlayerRef player);
	void RemovePlayer(int64 playerId);
	PlayerRef FindPlayer(int64 playerId);

	void CopyChannelProtocol(Protocol::Channel* pkt);
	Protocol::LobbyInfo* GetLobbyInfoProtocol();

public:
	void Broadcast(SendBufferRef sendBuffer);

	int64 GetId() { return _id; }

private:
	USE_LOCK;
	HashMap<int64, RoomRef> _rooms;
	HashMap<int64, PlayerRef> _players;

private:
	int32 _increaseId = 1;

	int32 _id;
	int32 _maxPlayerCount = 0;
	int32 _currentPlayerCount = 0;
};
