#pragma once
#include "Protocol.pb.h"

using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum : uint16
{
	PKT_C_PING = 1000,
	PKT_S_PING = 1001,
	PKT_C_LOGIN = 1002,
	PKT_S_LOGIN = 1003,
	PKT_C_CHANNELCHOICE = 1004,
	PKT_S_CHANNELCHOICE = 1005,
	PKT_C_CHANNELCHAT = 1006,
	PKT_S_CHANNELCHAT = 1007,
	PKT_C_MAKEROOM = 1008,
	PKT_S_MAKEROOM = 1009,
	PKT_S_CHANNELUPDATE = 1010,
	PKT_C_ROOMENTER = 1011,
	PKT_S_ROOMENTER = 1012,
	PKT_C_ROOMLEAVE = 1013,
	PKT_S_ROOMUPDATE = 1014,
	PKT_C_ROOMREADY = 1015,
	PKT_C_ROOMCHAT = 1016,
	PKT_S_ROOMCHAT = 1017,
	PKT_C_ROOMSTART = 1018,
	PKT_S_ROOMSTART = 1019,
	PKT_C_MOVE = 1020,
	PKT_S_MOVE = 1021,
	PKT_C_BOMB = 1022,
	PKT_S_BOMB = 1023,
	PKT_S_BOMBEND = 1024,
	PKT_S_ITEMSPAWN = 1025,
	PKT_S_DEAD = 1026,
	PKT_S_ITEMACQUISITION = 1027,
	PKT_S_GAMEEND = 1028,
	PKT_S_ROOMBACK = 1029,
};

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_C_PING(PacketSessionRef& session, Protocol::C_PING& pkt);
bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt);
bool Handle_C_CHANNELCHOICE(PacketSessionRef& session, Protocol::C_CHANNELCHOICE& pkt);
bool Handle_C_CHANNELCHAT(PacketSessionRef& session, Protocol::C_CHANNELCHAT& pkt);
bool Handle_C_MAKEROOM(PacketSessionRef& session, Protocol::C_MAKEROOM& pkt);
bool Handle_C_ROOMENTER(PacketSessionRef& session, Protocol::C_ROOMENTER& pkt);
bool Handle_C_ROOMLEAVE(PacketSessionRef& session, Protocol::C_ROOMLEAVE& pkt);
bool Handle_C_ROOMREADY(PacketSessionRef& session, Protocol::C_ROOMREADY& pkt);
bool Handle_C_ROOMCHAT(PacketSessionRef& session, Protocol::C_ROOMCHAT& pkt);
bool Handle_C_ROOMSTART(PacketSessionRef& session, Protocol::C_ROOMSTART& pkt);
bool Handle_C_MOVE(PacketSessionRef& session, Protocol::C_MOVE& pkt);
bool Handle_C_BOMB(PacketSessionRef& session, Protocol::C_BOMB& pkt);

class ClientPacketHandler
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;
		GPacketHandler[PKT_C_PING] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_PING>(Handle_C_PING, session, buffer, len); };
		GPacketHandler[PKT_C_LOGIN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_LOGIN>(Handle_C_LOGIN, session, buffer, len); };
		GPacketHandler[PKT_C_CHANNELCHOICE] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_CHANNELCHOICE>(Handle_C_CHANNELCHOICE, session, buffer, len); };
		GPacketHandler[PKT_C_CHANNELCHAT] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_CHANNELCHAT>(Handle_C_CHANNELCHAT, session, buffer, len); };
		GPacketHandler[PKT_C_MAKEROOM] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_MAKEROOM>(Handle_C_MAKEROOM, session, buffer, len); };
		GPacketHandler[PKT_C_ROOMENTER] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_ROOMENTER>(Handle_C_ROOMENTER, session, buffer, len); };
		GPacketHandler[PKT_C_ROOMLEAVE] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_ROOMLEAVE>(Handle_C_ROOMLEAVE, session, buffer, len); };
		GPacketHandler[PKT_C_ROOMREADY] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_ROOMREADY>(Handle_C_ROOMREADY, session, buffer, len); };
		GPacketHandler[PKT_C_ROOMCHAT] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_ROOMCHAT>(Handle_C_ROOMCHAT, session, buffer, len); };
		GPacketHandler[PKT_C_ROOMSTART] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_ROOMSTART>(Handle_C_ROOMSTART, session, buffer, len); };
		GPacketHandler[PKT_C_MOVE] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_MOVE>(Handle_C_MOVE, session, buffer, len); };
		GPacketHandler[PKT_C_BOMB] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_BOMB>(Handle_C_BOMB, session, buffer, len); };
	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, uint32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(Protocol::S_PING& packet) { return MakeSendBuffer(packet, PKT_S_PING); }
	static SendBufferRef MakeSendBuffer(Protocol::S_LOGIN& packet) { return MakeSendBuffer(packet, PKT_S_LOGIN); }
	static SendBufferRef MakeSendBuffer(Protocol::S_CHANNELCHOICE& packet) { return MakeSendBuffer(packet, PKT_S_CHANNELCHOICE); }
	static SendBufferRef MakeSendBuffer(Protocol::S_CHANNELCHAT& packet) { return MakeSendBuffer(packet, PKT_S_CHANNELCHAT); }
	static SendBufferRef MakeSendBuffer(Protocol::S_MAKEROOM& packet) { return MakeSendBuffer(packet, PKT_S_MAKEROOM); }
	static SendBufferRef MakeSendBuffer(Protocol::S_CHANNELUPDATE& packet) { return MakeSendBuffer(packet, PKT_S_CHANNELUPDATE); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ROOMENTER& packet) { return MakeSendBuffer(packet, PKT_S_ROOMENTER); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ROOMUPDATE& packet) { return MakeSendBuffer(packet, PKT_S_ROOMUPDATE); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ROOMCHAT& packet) { return MakeSendBuffer(packet, PKT_S_ROOMCHAT); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ROOMSTART& packet) { return MakeSendBuffer(packet, PKT_S_ROOMSTART); }
	static SendBufferRef MakeSendBuffer(Protocol::S_MOVE& packet) { return MakeSendBuffer(packet, PKT_S_MOVE); }
	static SendBufferRef MakeSendBuffer(Protocol::S_BOMB& packet) { return MakeSendBuffer(packet, PKT_S_BOMB); }
	static SendBufferRef MakeSendBuffer(Protocol::S_BOMBEND& packet) { return MakeSendBuffer(packet, PKT_S_BOMBEND); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ITEMSPAWN& packet) { return MakeSendBuffer(packet, PKT_S_ITEMSPAWN); }
	static SendBufferRef MakeSendBuffer(Protocol::S_DEAD& packet) { return MakeSendBuffer(packet, PKT_S_DEAD); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ITEMACQUISITION& packet) { return MakeSendBuffer(packet, PKT_S_ITEMACQUISITION); }
	static SendBufferRef MakeSendBuffer(Protocol::S_GAMEEND& packet) { return MakeSendBuffer(packet, PKT_S_GAMEEND); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ROOMBACK& packet) { return MakeSendBuffer(packet, PKT_S_ROOMBACK); }

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