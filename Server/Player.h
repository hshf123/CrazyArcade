#pragma once
#include "GameObject.h"

using PlayerInfo = Protocol::PPlayer;
using ItemType = Protocol::PItemType;

class Player : public GameObject
{
public:
	bool AddBomb();
	void SubBomb();
	void ApplyItemAbility(ItemType type);

	void OnTrap();
	void OutTrap();
	void OnDead();

public:
	Vector2Int GetCellPos() { return Vector2Int(PosInfo.cellpos().posx(), PosInfo.cellpos().posy()); }
	Vector2 GetWorldPos() { return Vector2(PosInfo.worldpos().posx(), PosInfo.worldpos().posy()); }
	void SetCellPos(Vector2Int pos);
	void SetCellPos(Protocol::PCellPos& pkt);
	void SetWorldPos(Vector2 pos);
	void SetWorldPos(Protocol::PWorldPos& pkt);

public:
	void CopyPlayerProtocol(Protocol::PPlayer* pkt);
	Protocol::PPlayer* GetPlayerProtocol();
	void SetClientSession(ClientSessionRef session) { _ownerSession = session; }
	ClientSessionRef GetClientSession() { return _ownerSession.lock(); }
	void SetRoom(RoomRef room) { _room = room; }
	RoomRef GetRoom() { return _room; }
	void Send(SendBufferRef sendBuffer);

public:
	PlayerInfo PlayerInfo;
	int32 Kill;
	int32 Rank = 1;

private:
	ClientSessionWeakRef _ownerSession;
	RoomRef _room;
	float _originalSpeed;
};
