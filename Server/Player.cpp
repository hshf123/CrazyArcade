#include "pch.h"
#include "Player.h"
#include "ClientSession.h"


void Player::CopyPlayerProtocol(Protocol::PPlayer* pkt)
{
	pkt->CopyFrom(PlayerInfo);
}

Protocol::PPlayer* Player::GetPlayerProtocol()
{
	Protocol::PPlayer* pkt = new Protocol::PPlayer();
	pkt->CopyFrom(PlayerInfo);
	return pkt;
}

void Player::CopyPositionInfoProtocol(Protocol::PPositionInfo* pkt)
{
	pkt->CopyFrom(PosInfo);
}

Protocol::PPositionInfo* Player::GetPositionInfoProtocol()
{
	Protocol::PPositionInfo* pkt = new Protocol::PPositionInfo();
	pkt->CopyFrom(PosInfo);
	return pkt;
}

void Player::Send(SendBufferRef sendBuffer)
{
	_ownerSession.lock()->Send(sendBuffer);
}
