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
	void Send(SendBufferRef sendBuffer);

private:
	ClientSessionWeakRef _ownerSession;
	USE_LOCK;
	
	wstring _playerid;
	wstring _name;
	int32 _level;
	float _exp;
	int64 _id;
};
