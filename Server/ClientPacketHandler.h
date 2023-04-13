#pragma once
#include "Protocol.pb.h"

using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum : uint16
{
	PKT_C_LOGIN = 1000,
	PKT_S_LOGIN = 1001,
	PKT_C_CHANNELCHOIC = 1002,
	PKT_S_CHANNELCHOIC = 1003,
	PKT_C_CHANNELCHAT = 1004,
	PKT_S_CHANNELCHAT = 1005,
	PKT_C_MAKEROOM = 1006,
	PKT_S_MAKEROOM = 1007,
	PKT_S_CHANNELUPDATE = 1008,
	PKT_C_ROOMENTER = 1009,
	PKT_S_ROOMENTER = 1010,
	PKT_S_ROOMUPDATE = 1011,
};

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt);
bool Handle_C_CHANNELCHOIC(PacketSessionRef& session, Protocol::C_CHANNELCHOIC& pkt);
bool Handle_C_CHANNELCHAT(PacketSessionRef& session, Protocol::C_CHANNELCHAT& pkt);
bool Handle_C_MAKEROOM(PacketSessionRef& session, Protocol::C_MAKEROOM& pkt);
bool Handle_C_ROOMENTER(PacketSessionRef& session, Protocol::C_ROOMENTER& pkt);

class ClientPacketHandler
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;
		GPacketHandler[PKT_C_LOGIN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_LOGIN>(Handle_C_LOGIN, session, buffer, len); };
		GPacketHandler[PKT_C_CHANNELCHOIC] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_CHANNELCHOIC>(Handle_C_CHANNELCHOIC, session, buffer, len); };
		GPacketHandler[PKT_C_CHANNELCHAT] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_CHANNELCHAT>(Handle_C_CHANNELCHAT, session, buffer, len); };
		GPacketHandler[PKT_C_MAKEROOM] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_MAKEROOM>(Handle_C_MAKEROOM, session, buffer, len); };
		GPacketHandler[PKT_C_ROOMENTER] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_ROOMENTER>(Handle_C_ROOMENTER, session, buffer, len); };
	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, uint32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(Protocol::S_LOGIN& packet) { return MakeSendBuffer(packet, PKT_S_LOGIN); }
	static SendBufferRef MakeSendBuffer(Protocol::S_CHANNELCHOIC& packet) { return MakeSendBuffer(packet, PKT_S_CHANNELCHOIC); }
	static SendBufferRef MakeSendBuffer(Protocol::S_CHANNELCHAT& packet) { return MakeSendBuffer(packet, PKT_S_CHANNELCHAT); }
	static SendBufferRef MakeSendBuffer(Protocol::S_MAKEROOM& packet) { return MakeSendBuffer(packet, PKT_S_MAKEROOM); }
	static SendBufferRef MakeSendBuffer(Protocol::S_CHANNELUPDATE& packet) { return MakeSendBuffer(packet, PKT_S_CHANNELUPDATE); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ROOMENTER& packet) { return MakeSendBuffer(packet, PKT_S_ROOMENTER); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ROOMUPDATE& packet) { return MakeSendBuffer(packet, PKT_S_ROOMUPDATE); }

private:
	template<class PacketType, class ProcessFunc>
	static bool HandlePacket(ProcessFunc func, PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketType pkt;
		if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
			return false;

		return func(session, pkt);
	}

	template<class T>
	static SendBufferRef MakeSendBuffer(T& pkt, uint16 pktId)
	{
		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;
		ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}
};