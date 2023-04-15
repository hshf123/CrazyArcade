#pragma once

using PositionInfo = Protocol::PPositionInfo;
using PlayerInfo = Protocol::PPlayer;

class Player
{
public:
	void CopyPlayerProtocol(Protocol::PPlayer* pkt);
	Protocol::PPlayer* GetPlayerProtocol();
	void CopyPositionInfoProtocol(Protocol::PPositionInfo* pkt);
	Protocol::PPositionInfo* GetPositionInfoProtocol();

	void SetClientSession(ClientSessionRef session) { _ownerSession = session; }
	ClientSessionRef GetClientSession() { return _ownerSession.lock(); }
	
	void Send(SendBufferRef sendBuffer);

public:
	PlayerInfo PlayerInfo;
	PositionInfo PosInfo;

private:
	ClientSessionWeakRef _ownerSession;
};
