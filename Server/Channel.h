#pragma once
#include "ClientPacketHandler.h"

using ChannelInfo = Protocol::PChannel;

// RoomManager °â¿ë
class Channel : public enable_shared_from_this<Channel>
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
	void Broadcast(SendBufferRef sendBuffer, ClientSessionRef exceptSession = nullptr);
	template <class T> void Broadcast(T pkt, ClientSessionRef exceptSession = nullptr);

public:
	ChannelInfo ChannelInfo;

private:
	USE_LOCK;
	HashMap<int64, RoomRef> _rooms;
	HashMap<int64, PlayerRef> _players;

private:
	int32 _increaseId = 1;
};

template <class T>
void Channel::Broadcast(T pkt, ClientSessionRef exceptSession/*= nullptr*/)
{
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(pkt);
	Broadcast(sendBuffer, exceptSession);
}