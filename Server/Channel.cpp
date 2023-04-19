#include "pch.h"
#include "Channel.h"
#include "Player.h"
#include "Room.h"
#include "Protocol.pb.h"
#include "ClientPacketHandler.h"

void Channel::AddRoom(int64 playerId, const string& roomName, int32 maxPlayerCount /*= 8*/)
{
	wstringstream log;
	WRITE_LOCK;
	// TODO : increaseId ����
	RoomRef room = MakeShared<Room>(_increaseId, roomName, maxPlayerCount);
	_rooms.insert({ _increaseId++, room });

	PlayerRef player = FindPlayer(playerId);
	if (player == nullptr)
		return;

	room->InsertPlayer(player);
	room->SetLeader(playerId);
	RemovePlayer(playerId);

	{
		// ���� ���� �÷��̾�� ����
		Protocol::S_MAKEROOM makeRoomPkt;
		makeRoomPkt.set_success(true);
		makeRoomPkt.set_allocated_room(room->GetRoomProtocol());
		SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(makeRoomPkt);
		player->Send(sendBuffer);
	}
	{
		// �κ� �ִ� �÷��̾�鿡�� ����
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
	_rooms.erase(roomId);
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
}

void Channel::RemovePlayer(int64 playerId)
{
	WRITE_LOCK;
	_players.erase(playerId);
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
	Protocol::PChannel* pkt = new Protocol::PChannel();
	pkt->CopyFrom(ChannelInfo);
	return pkt;
}

Vector<Protocol::PRoom> Channel::GetRoomsProtocol()
{
	Vector<Protocol::PRoom> res;
	READ_LOCK;
	for (auto& p : _rooms)
	{
		res.push_back(*p.second->GetRoomProtocol());
	}
	return res;
}

void Channel::Broadcast(SendBufferRef sendBuffer)
{
	READ_LOCK;
	for (auto& p : _players)
	{
		p.second->Send(sendBuffer);
	}
}
