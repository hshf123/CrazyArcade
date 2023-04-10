#include "pch.h"
#include "ClientSessionManager.h"
#include "ClientSession.h"
#include "SendBuffer.h"
#include "Player.h"

ClientSessionManager GSessionManager;

void ClientSessionManager::Add(ClientSessionRef session)
{
	WRITE_LOCK;
	_sessions.insert(session);
}

void ClientSessionManager::Remove(ClientSessionRef session)
{
	WRITE_LOCK;
	_sessions.erase(session);
}
