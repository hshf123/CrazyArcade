#pragma once

using ChannelInfo = Protocol::PChannel;

// RoomManager °â¿ë
class Channel
{
public:
	void AddRoom(int64 playerId, const string& roomName, int32 maxPlayerCount = 8);
	void RemoveRoom(int32 roomId);
	RoomRef FindRoom(int32 roomId);

	void InsertPlayer(PlayerRef player);
	void RemovePlayer(int64 playerId);
	PlayerRef FindPlayer(int64 playerId);

	void CopyChannelProtocol(Protocol::PChannel* pkt);
	Protocol::PChannel* GetChannelProtocol();
	Vector<Protocol::PRoom> GetRoomsProtocol();

public:
	void Broadcast(SendBufferRef sendBuffer);

public:
	ChannelInfo ChannelInfo;

private:
	USE_LOCK;
	HashMap<int64, RoomRef> _rooms;
	HashMap<int64, PlayerRef> _players;

private:
	int32 _increaseId = 1;
};
