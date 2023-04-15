#include "pch.h"
#include "ClientSession.h"
#include "ClientSessionManager.h"
#include "SendBuffer.h"
#include "ClientPacketHandler.h"
#include "Player.h"
#include "Protocol.pb.h"

void ClientSession::OnConnected(NetAddress netAddr)
{
	GSessionManager.Add(static_pointer_cast<ClientSession>(shared_from_this()));
	wcout << netAddr.GetIpAddress() << " | " << netAddr.GetPort() << endl;
}

void ClientSession::OnDisconnected()
{
	GSessionManager.Remove(static_pointer_cast<ClientSession>(shared_from_this()));
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
