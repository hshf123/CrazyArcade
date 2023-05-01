#include "pch.h"
#include "Channel.h"
#include "Player.h"
#include "Room.h"
#include "Protocol.pb.h"

void Channel::Update()
{
	for (auto& p : _rooms)
	{
		p.second->Update();
	}
}

void Channel::AddRoom(int64 playerId, const string& roomName, int32 maxPlayerCount /*= 8*/)
{
	wstringstream log;
	WRITE_LOCK;
	// TODO : increaseId 조절
	RoomRef room = MakeShared<Room>(_increaseId, roomName, maxPlayerCount);
	room->SetChannel(shared_from_this());
	_rooms.insert({ _increaseId++, room });

	PlayerRef player = FindPlayer(playerId);
	if (player == nullptr)
		return;

	room->InsertPlayer(player);
	room->SetLeader(playerId);
	RemovePlayer(playerId);

	{
		// 방을 만든 플레이어에게 전송
		Protocol::S_MAKEROOM makeRoomPkt;
		makeRoomPkt.set_success(true);
		makeRoomPkt.set_allocated_room(room->GetRoomProtocol());
		SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(makeRoomPkt);
		player->Send(sendBuffer);
	}
	{
		// 로비에 있는 플레이어들에게 전송
		Protocol::S_CHANNELUPDATE channelUpdatePkt;
		for (Protocol::PRoom r : GetRoomsProtocol())
		{
			Protocol::PRoom* room = channelUpdatePkt.add_rooms();
			room->CopyFrom(r);
		}
		SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(channelUpdatePkt);
		Broadcast(sendBuffer);
	}

	log << "PLAYER ID : " << player->PlayerInfo.id() << L" MAKE ROOM, ROOM ID : " << player->PlayerInfo.roomid();
	Utils::Log(log);
}

void Channel::RemoveRoom(int32 roomId)
{
	WRITE_LOCK;
	RoomRef room = FindRoom(roomId);
	_rooms.erase(roomId);
	if (room == nullptr)
		return;

	room->SetChannel(nullptr);
	room = nullptr;

	Protocol::S_CHANNELUPDATE channelUpdatePkt;
	for (Protocol::PRoom r : GetRoomsProtocol())
	{
		Protocol::PRoom* room = channelUpdatePkt.add_rooms();
		room->CopyFrom(r);
	}
	Broadcast(channelUpdatePkt);

	wstringstream log;
	log << L"CHANNEL ID : " << ChannelInfo.channelid() << L" REMOVE ROOM ID : " << roomId;
	Utils::Log(log);
}

RoomRef Channel::FindRoom(int32 roomId)
{
	READ_LOCK;
	auto findIt = _rooms.find(roomId);
	if (findIt == _rooms.end())
		return nullptr;

	return findIt->second;
}

void Channel::InsertPlayer(PlayerRef player)
{
	WRITE_LOCK;
	_players.insert({ player->PlayerInfo.id(), player });
	player->PlayerInfo.set_channelid(ChannelInfo.channelid());

	if (ChannelInfo.currentplayercount() > ChannelInfo.maxplayercount())
	{
		RemovePlayer(player->PlayerInfo.id());
		return;
	}

	Protocol::S_CHANNELCHOICE channelChoicePkt;
	channelChoicePkt.set_success(true);
	channelChoicePkt.set_channelid(ChannelInfo.channelid());
	for (auto room : GetRoomsProtocol())
	{
		auto* r = channelChoicePkt.add_rooms();
		r->CopyFrom(room);
	}
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(channelChoicePkt);
	player->Send(sendBuffer);

	// // 해당 채널 로비에 broadcast
	// Protocol::S_CHANNELUPDATE channelUpdatePkt;
	// for (Protocol::PRoom r : GetRoomsProtocol())
	// {
	// 	Protocol::PRoom* room = channelUpdatePkt.add_rooms();
	// 	room->CopyFrom(r);
	// }
	// Broadcast(channelUpdatePkt, player->GetClientSession());

	wstringstream log;
	log << L"PLAYER ID : " << player->PlayerInfo.id() << L" ENTER CHANNEL ID : " << ChannelInfo.channelid() << L" CURRENT PLAYER COUNT : " << ChannelInfo.currentplayercount();
	Utils::Log(log);
}

void Channel::RemovePlayer(int64 playerId)
{
	WRITE_LOCK;
	_players.erase(playerId);
	ChannelInfo.set_currentplayercount(ChannelInfo.currentplayercount() - 1);
}

PlayerRef Channel::FindPlayer(int64 playerId)
{
	READ_LOCK;
	auto findIt = _players.find(playerId);
	if (findIt == _players.end())
		return nullptr;

	return findIt->second;
}

void Channel::CopyChannelProtocol(Protocol::PChannel* pkt)
{
	READ_LOCK;
	pkt->CopyFrom(ChannelInfo);
}

Protocol::PChannel* Channel::GetChannelProtocol()
{
	Protocol::PChannel* pkt = ChannelInfo.New();
	pkt->CopyFrom(ChannelInfo);
	Vector<Protocol::PRoom> vec = GetRoomsProtocol();
	pkt->clear_currentplayercount();
	pkt->set_currentplayercount(_players.size());
	for (auto& v : vec)
		pkt->set_currentplayercount(pkt->currentplayercount() + v.currentplayercount());
	return pkt;
}

Vector<Protocol::PRoom> Channel::GetRoomsProtocol()
{
	Vector<Protocol::PRoom> res;
	READ_LOCK;
	for (auto& p : _rooms)
		res.push_back(*p.second->GetRoomProtocol());
	return res;
}

void Channel::Broadcast(SendBufferRef sendBuffer, ClientSessionRef exceptSession /*= nullptr*/)
{
	READ_LOCK;
	for (auto& p : _players)
	{
		if (exceptSession != nullptr && p.second->GetClientSession() == exceptSession)
			continue;
		p.second->Send(sendBuffer);
	}
}
