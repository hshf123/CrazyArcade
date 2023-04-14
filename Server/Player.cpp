#include "pch.h"
#include "Player.h"
#include "ClientSession.h"

Player::Player(ClientSessionRef clientSession, wstring name, wstring playerid, int32 level, float exp, int64 id)
	: _ownerSession(clientSession), _name(name), _playerid(playerid), _level(level), _exp(exp), _id(id)
{

}

void Player::CopyPlayerProtocol(Protocol::Player* pkt)
{
	READ_LOCK;
	pkt->set_playerid(_id);
	pkt->set_level(_level);
	pkt->set_name(GetName());
	pkt->set_roomidx(_roomIdx);
	pkt->set_ready(_ready);
}

void Player::Send(SendBufferRef sendBuffer)
{
	_ownerSession.lock()->Send(sendBuffer);
}
