#include "pch.h"
#include "Player.h"
#include "ClientSession.h"
#include "ForestMap.h"
#include "ThreadManager.h"
#include "Room.h"

bool Player::AddBomb()
{
	if (PlayerInfo.bombcount() < PlayerInfo.maxbombcount())
	{
		PlayerInfo.set_bombcount(PlayerInfo.bombcount() + 1);
		wstringstream log;
		log << L"PLAYER ID : " << PlayerInfo.id() << L" BOMB COUNT ";
		log << PlayerInfo.bombcount() << L"/" << PlayerInfo.maxbombcount();
		Utils::Log(log);
		return true;
	}
	return false;
}

void Player::SubBomb()
{
	if (PlayerInfo.bombcount() > 0)
	{
		PlayerInfo.set_bombcount(PlayerInfo.bombcount() - 1);
		wstringstream log;
		log << L"PLAYER ID : " << PlayerInfo.id() << L" BOMB COUNT ";
		log << PlayerInfo.bombcount() << L"/" << PlayerInfo.maxbombcount();
		Utils::Log(log);
	}
}

void Player::ApplyItemAbility(ItemType type)
{
	switch (type)
	{
	case ItemType::INCBOMBCOUNT:
		if(PlayerInfo.maxbombcount() < 9)
			PlayerInfo.set_maxbombcount(PlayerInfo.maxbombcount() + 1);
		break;
	case ItemType::INCBOMBRANGE:
		if(PlayerInfo.bombrange() < 8)
			PlayerInfo.set_bombrange(PlayerInfo.bombrange() + 1);
		break;
	case ItemType::INCSPEED:
		PlayerInfo.set_speed(PlayerInfo.speed() + 0.5f);
		break; break;
	case ItemType::MAXBOMBRANGE:
		PlayerInfo.set_bombrange(9);
		break;
	default:
		break;
	}

#pragma region LOG
	wstringstream log;
	log << L"Player ID : ";
	log << PlayerInfo.id();
	log << L" | GET ITEM TYPE (";
	log << typeid(type).name();
	log << L")";
	Utils::Log(log);
#pragma endregion
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

void Player::SetCellPos(Vector2Int pos)
{
	Protocol::PCellPos* cellpos = new Protocol::PCellPos();
	cellpos->set_posx(pos.x);
	cellpos->set_posy(pos.y);
	PosInfo.set_allocated_cellpos(cellpos);
}

void Player::SetCellPos(Protocol::PCellPos* pkt)
{
	auto cellpos = pkt->New();
	cellpos->set_posx(pkt->posx());
	cellpos->set_posy(pkt->posy());
	PosInfo.set_allocated_cellpos(cellpos);
}

void Player::SetWorldPos(Vector2 pos)
{
	Protocol::PWorldPos* worldPos = new Protocol::PWorldPos();
	worldPos->set_posx(pos.x);
	worldPos->set_posy(pos.y);
	PosInfo.set_allocated_worldpos(worldPos);
}

void Player::SetWorldPos(Protocol::PWorldPos* pkt)
{
	auto worldPos = pkt->New();
	worldPos->set_posx(pkt->posx());
	worldPos->set_posy(pkt->posy());
	PosInfo.set_allocated_worldpos(worldPos);
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
