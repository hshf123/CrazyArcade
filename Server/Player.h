#pragma once
#include "GameObject.h"

using PlayerInfo = Protocol::PPlayer;

class Player : public GameObject
{
public:
	Vector2Int GetCellPos() { return Vector2Int(PosInfo.cellpos().posx(), PosInfo.cellpos().posy()); }
	Vector2 GetWorldPos() { return Vector2(PosInfo.worldpos().posx(), PosInfo.worldpos().posy()); }

	bool AddBomb();
	void SubBomb();

	void OnTrap();
	void OutTrap();
	void OnDead();

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

private:
	ClientSessionWeakRef _ownerSession;
	RoomRef _room;
	float _originalSpeed;
};
