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
	PlayerRef player = MyPlayer;
	if (player != nullptr)
	{
		RoomRef room = player->GetRoom();
		if (room != nullptr)
		{
			room->RemovePlayer(player->PlayerInfo.id());

			ChannelRef channel = room->GetChannel();
			if (channel != nullptr)
			{
				channel->RemovePlayer(player->PlayerInfo.id());
			}
		}
	}

	wstringstream log;
	log << L"PLAYER ID : " << player->PlayerInfo.id() << L" DISCONNECTED";
	Utils::Log(log);
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
