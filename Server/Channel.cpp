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
		Protocol::RoomInfo* roomInfo = room->GetRoomInfoProtocol();
		makeRoomPkt.set_allocated_roominfo(roomInfo);
		SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(makeRoomPkt);
		player->Send(sendBuffer);
	}

	{
		// �κ� �ִ� �÷��̾�鿡�� ����
		Protocol::S_CHANNELUPDATE channelUpdatePkt;
		Protocol::LobbyInfo* lobbyInfo = GetLobbyInfoProtocol();
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

void Channel::CopyChannelProtocol(Protocol::Channel* pkt)
{
	READ_LOCK;
	pkt->set_channelid(_id);
	pkt->set_maxplayercount(_maxPlayerCount);
	pkt->set_currentplayercount(_currentPlayerCount);
}

Protocol::LobbyInfo* Channel::GetLobbyInfoProtocol()
{
	Protocol::LobbyInfo* pkt = new Protocol::LobbyInfo();
	READ_LOCK;
	pkt->set_roomcount(_rooms.size());
	for (auto p : _rooms)
	{
		Protocol::Room* room = pkt->add_rooms();
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
