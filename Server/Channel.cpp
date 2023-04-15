#include "pch.h"
#include "Channel.h"
#include "Player.h"
#include "Room.h"
#include "Protocol.pb.h"
#include "ClientPacketHandler.h"

Channel::Channel(int64 id, int32 maxPlayerCount)
	: _id(id), _maxPlayerCount(maxPlayerCount), _currentPlayerCount(0)
{

}

void Channel::AddRoom(int64 playerId, const string& roomName, int32 maxPlayerCount /*= 8*/)
{
	WRITE_LOCK;
	// TODO : increaseId 조절
	RoomRef room = MakeShared<Room>(_increaseId, roomName, maxPlayerCount);
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
		Protocol::PLobbyInfo* lobbyInfo = GetLobbyInfoProtocol();
		channelUpdatePkt.set_allocated_lobbyinfo(lobbyInfo);
		SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(channelUpdatePkt);
		Broadcast(sendBuffer);
	}
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
	_players.insert({ player->GetId(), player });
	player->SetChannelD(_id);
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
	pkt->set_channelid(_id);
	pkt->set_maxplayercount(_maxPlayerCount);
	pkt->set_currentplayercount(_currentPlayerCount);
}

Protocol::PLobbyInfo* Channel::GetLobbyInfoProtocol()
{
	Protocol::PLobbyInfo* pkt = new Protocol::PLobbyInfo();
	READ_LOCK;
	pkt->set_roomcount(_rooms.size());
	for (auto& p : _rooms)
	{
		Protocol::PRoom* room = pkt->add_rooms();
		p.second->CopyRoomProtocol(room);
	}
	return pkt;
}

void Channel::Broadcast(SendBufferRef sendBuffer)
{
	READ_LOCK;
	for (auto& p : _players)
	{
		p.second->Send(sendBuffer);
	}
}
