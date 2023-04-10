#include "pch.h"
#include "Player.h"

Player::Player(ClientSessionRef clientSession, wstring name, wstring playerid, int32 level, float exp, int64 id)
	: _ownerSession(clientSession), _name(name), _playerid(playerid), _level(level), _exp(exp), _id(id)
{

}
