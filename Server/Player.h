#pragma once

class Player
{
public:
	Player(ClientSessionRef clientSession, wstring name, wstring playerid, int32 level, float exp, int64 id);

	int64 GetId() { return _id; }

private:
	ClientSessionWeakRef _ownerSession;
	
	wstring _playerid;
	wstring _name;
	int32 _level;
	float _exp;
	int64 _id;
};
