#pragma once

class Player
{
public:
	Player(ClientSessionRef clientSession, wstring name, wstring playerid, int32 level, float exp, int64 id);

	void CopyPlayerProtocol(Protocol::Player* pkt);

public:
	int64 GetId() { return _id; }
	string GetName() { return Utils::ConvertWStringToString(_name); }
	int32 GetLevel() { return _level; }
	void SetChannelD(int32 channelId) { _channelId = channelId; }
	int32 GetChannelID() { return _channelId; }
	void SetRoomID(int32 roomId) { _roomId = roomId; }
	int32 GetRoomID() { return _roomId; }
	void SetRoomIdx(int32 roomIdx) { _roomIdx = roomIdx; }
	int32 GetRoomIdx() { return _roomIdx; }
	void SetReady() { _ready = !_ready; }

	void Send(SendBufferRef sendBuffer);

private:
	ClientSessionWeakRef _ownerSession;
	USE_LOCK;
	
	wstring _playerid;
	wstring _name;
	int32 _level;
	float _exp;
	int64 _id;

	int32 _channelId;
	int32 _roomId;
	int32 _roomIdx;
	bool _ready = false;
};
