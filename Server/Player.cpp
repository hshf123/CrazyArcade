#include "pch.h"
#include "Player.h"
#include "ClientSession.h"
#include "ForestMap.h"

bool Player::AddBomb()
{
	int32 currentBombCount = PlayerInfo.bombcount();
	if (currentBombCount < PlayerInfo.maxbombcount())
	{
		PlayerInfo.set_bombcount(currentBombCount + 1);
		return true;
	}
	return false;
}

void Player::SubBomb()
{
	int32 currentBombCount = PlayerInfo.bombcount();
	if (currentBombCount >= 0)
		PlayerInfo.set_bombcount(currentBombCount - 1);
}

void Player::OnTrap()
{
	PosInfo.set_state(Protocol::INTRAP);
}

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

void Player::Send(SendBufferRef sendBuffer)
{
	_ownerSession.lock()->Send(sendBuffer);
}
