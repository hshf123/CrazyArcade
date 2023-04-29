#pragma once
#include "Protocol.pb.h"
#include "ClientPacketHandler.h"

using RoomState = Protocol::PRoomState;

class Room : public enable_shared_from_this<Room>
{
public:
	Room(int64 id, const string& roomName, int32 maxPlayerCount);

	void InsertPlayer(PlayerRef player);
	void RemovePlayer(int64 playerId);
	PlayerRef FindPlayer(int64 playerId);
	void SetIdx(PlayerRef player);
	void PlayerDead(PlayerRef player);

public:
	bool CanGameStart();
	void GameInit();
	void Update();
	void GameEnd();
	Protocol::PPositionInfo* GetBasicPosInfo(int32 idx);

public:
	void CopyRoomProtocol(Protocol::PRoom* pkt);
	Protocol::PRoom* GetRoomProtocol();

	int32 GetId() { return _roomId; }
	string GetRoomName() { return Utils::ConvertWStringToString(_roomName); }
	void SetLeader(int64 playerId);
	PlayerRef GetLeader() { return FindPlayer(_leaderId); }

	void SetChannel(ChannelRef channel) { _channel = channel; }
	ChannelRef GetChannel() { return _channel; }

	void Broadcast(SendBufferRef sendBuffer, ClientSessionRef exceptSession = nullptr);
	template <class T>
	void Broadcast(T pkt, ClientSessionRef exceptSession = nullptr);

public:
	void HandleChat(PlayerRef player, Protocol::C_ROOMCHAT& pkt);
	void HandleMove(PlayerRef player, Protocol::C_MOVE& pkt);
	void HandleBomb(PlayerRef player, Protocol::C_BOMB& pkt);
	void HandleBombEnd(PlayerRef player, Protocol::C_BOMBEND& pkt);

private:
	USE_LOCK;
	uint64 _endTime = 0;
	HashMap<int64, PlayerRef> _players;
	HashMap<int32, PlayerRef> _idxes;

private:
	ChannelRef _channel;

	int32 _roomId;
	wstring _roomName;
	int32 _maxPlayerCount = 0;
	int32 _currentPlayerCount = 0;

	int64 _leaderId;
	bool _benList[8];
	RoomState _state = RoomState::WAITING;

	ForestMapRef _forestMap;
	int32 _respawnPosX[8] = { -7,4,-7,4,-5,0,-5,2 };
	int32 _respawnPosY[8] = { 5,5,-6,-6,5,5,-6,-6 };
	int32 _rank;
};

template <class T>
void Room::Broadcast(T pkt, ClientSessionRef exceptSession /*= nullptr*/)
{
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(pkt);
	Broadcast(sendBuffer, exceptSession);
}
