#pragma once

using ClientSessionRef = shared_ptr<class ClientSession>;

class ClientSessionManager
{
public:
	void Add(ClientSessionRef session);
	void Remove(ClientSessionRef session);

private:
	USE_LOCK;
	Set<ClientSessionRef> _sessions;
};

extern ClientSessionManager GSessionManager;