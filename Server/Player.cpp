#include "pch.h"
#include "Player.h"
#include "ClientSession.h"

Player::Player(ClientSessionRef clientSession, wstring name, wstring playerid, int32 level, float exp, int64 id)
	: _ownerSession(clientSession), _name(name), _playerid(playerid), _level(level), _exp(exp), _id(id)
{

}

void Player::CopyPlayerProtocol(Protocol::PPlayer* pkt)
{
	READ_LOCK;
	pkt->set_playerid(GetPlayerId());
	pkt->set_name(GetName());
	pkt->set_level(_level);
	pkt->set_exp(_exp);
	pkt->set_id(_id);
	pkt->set_channelid(_channelId);
	pkt->set_roomid(_roomId);
	pkt->set_roomidx(_roomIdx);
	pkt->set_ready(_ready);

	pkt->set_speed(_speed);
	pkt->set_maxbombcount(_maxBombCount);
	pkt->set_bombcount(_bombCount);
	pkt->set_bombrange(_bombRange);
}

void Player::Send(SendBufferRef sendBuffer)
{
	_ownerSession.lock()->Send(sendBuffer);
}
