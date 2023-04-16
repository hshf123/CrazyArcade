#pragma once

using RoomState = Protocol::PRoomState;

class Room
{
public:
	Room(int64 id, const string& roomName, int32 maxPlayerCount);

	void InsertPlayer(PlayerRef player);
	void RemovePlayer(int64 playerId);
	PlayerRef FindPlayer(int64 playerId);
	void SetIdx(PlayerRef player);

public:
	bool CanGameStart();
	Protocol::PPositionInfo* GetBasicPosInfo(int32 idx);

public:
	void CopyRoomProtocol(Protocol::PRoom* pkt);
	Protocol::PRoom* GetRoomProtocol();

	int32 GetId() { return _roomId; }
	string GetRoomName() { return Utils::ConvertWStringToString(_roomName); }
	void SetLeader(int64 playerId);
	PlayerRef GetLeader() { return FindPlayer(_leaderId); }

	void Broadcast(SendBufferRef sendBuffer, ClientSessionRef exceptSession = nullptr);

private:
	USE_LOCK;
	HashMap<int64, PlayerRef> _players;
	HashMap<int32, PlayerRef> _idxes;

private:
	int32 _roomId;
	wstring _roomName;
	int32 _maxPlayerCount = 0;
	int32 _currentPlayerCount = 0;

	int64 _leaderId;
	bool _benList[8];
	RoomState _state = RoomState::WAITING;

	int32 _respawnPosX[8] = { -7,4,-7,4,-5,0,-5,2 };
	int32 _respawnPosY[8] = { 5,5,-6,-6,5,5,-6,-6 };
};
