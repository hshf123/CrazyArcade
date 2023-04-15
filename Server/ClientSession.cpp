#include "pch.h"
#include "ClientSession.h"
#include "ClientSessionManager.h"
#include "SendBuffer.h"
#include "ClientPacketHandler.h"
#include "Player.h"
#include "Protocol.pb.h"
#include "ChannelManager.h"
#include "Channel.h"
#include "Room.h"

void ClientSession::OnConnected(NetAddress netAddr)
{
	GSessionManager.Add(static_pointer_cast<ClientSession>(shared_from_this()));
	wcout << netAddr.GetIpAddress() << " | " << netAddr.GetPort() << endl;
}

void ClientSession::OnDisconnected()
{
	GSessionManager.Remove(static_pointer_cast<ClientSession>(shared_from_this()));
	PlayerRef player = MyPlayer.lock();
	if (player == nullptr)
		return;
		
	ChannelRef channel = ChannelManager::GetInstance()->FindChannel(player->PlayerInfo.channelid());
	if (channel == nullptr)
	{
		player = nullptr;
		return;
	}

	if (channel->FindPlayer(player->PlayerInfo.id()) != nullptr)
	{
		channel->RemovePlayer(player->PlayerInfo.id());
		player = nullptr;
		return;
	}

	RoomRef room = channel->FindRoom(player->PlayerInfo.roomid());
	if (room == nullptr)
	{
		player = nullptr;
		return;
	}

	room->RemovePlayer(player->PlayerInfo.id());
	player = nullptr;
}

void ClientSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketSessionRef session = GetPacketSessionRef();
	PacketHeader header = *reinterpret_cast<PacketHeader*>(buffer);

	ClientPacketHandler::HandlePacket(session, buffer, len);
}

void ClientSession::OnSend(int32 len)
{
}
