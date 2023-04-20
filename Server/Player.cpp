#include "pch.h"
#include "Player.h"
#include "ClientSession.h"
#include "ForestMap.h"
#include "ThreadManager.h"
#include "Room.h"

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
	_originalSpeed = PlayerInfo.speed();
	PlayerInfo.set_speed(0.1f);

	wstringstream log;
	log << PlayerInfo.id() << L" is ONTRAP";
	Utils::Log(log);

	GThreadManager->Launch([&]()
		{
			this_thread::sleep_for(6s);

			if (PosInfo.state() != Protocol::PPlayerState::INTRAP)
				return;

			_room->PlayerDead(static_pointer_cast<Player>(shared_from_this()));
		});
}

void Player::OutTrap()
{
	PosInfo.set_state(Protocol::OUTTRAP);
	_originalSpeed = PlayerInfo.speed();
	PlayerInfo.set_speed(_originalSpeed);
	// TODO 풀려나는 애니메이션 재생 후 idle로 변경
}

void Player::OnDead()
{
	PosInfo.set_state(Protocol::DEAD);
	// TODO OnDead
	Protocol::S_DEAD deadPkt;
	deadPkt.set_allocated_player(GetPlayerProtocol());
	deadPkt.set_allocated_posinfo(GetPositionInfoProtocol());
	if (_room != nullptr)
		_room->Broadcast(deadPkt);

	wstringstream log;
	log << PlayerInfo.id() << L" is DEAD";
	Utils::Log(log);
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
	ClientSessionRef session = _ownerSession.lock();
	if (session == nullptr)
		return;
	session->Send(sendBuffer);
}
