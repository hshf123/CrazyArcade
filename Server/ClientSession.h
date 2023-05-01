#pragma once

#include "Session.h"

class ClientSession : public PacketSession
{
public:
	~ClientSession()
	{
		wstringstream log;
		log << L"CLIENTSESSION DESTRUCTOR";
		Utils::Log(log);
	}

	void OnConnected(NetAddress netAddr) override;
	void OnDisconnected() override;
	void OnRecvPacket(BYTE* buffer, int32 len) override;
	void OnSend(int32 len) override;

public:
	PlayerRef MyPlayer;
};