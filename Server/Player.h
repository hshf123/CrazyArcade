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

public:
	void CopyPlayerProtocol(Protocol::PPlayer* pkt);
	Protocol::PPlayer* GetPlayerProtocol();

	void SetClientSession(ClientSessionRef session) { _ownerSession = session; }
	ClientSessionRef GetClientSession() { return _ownerSession.lock(); }
	
	void Send(SendBufferRef sendBuffer);

public:
	PlayerInfo PlayerInfo;
	uint64 MoveStartTime;

private:
	ClientSessionWeakRef _ownerSession;
};
