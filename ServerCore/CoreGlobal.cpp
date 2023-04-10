#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"
#include "DeadLockProfiler.h"
#include "Memory.h"
#include "SocketUtils.h"
#include "SendBuffer.h"
#include "DBConnectionPool.h"

ThreadManager* GThreadManager = nullptr;
DeadLockProfiler* GDeadLockProfiler = nullptr;
Memory* GMemory = nullptr;
SendBufferManager* GSendBufferManager = nullptr;
DBConnectionPool* GDBConnectionPool = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		GThreadManager = new ThreadManager();
		GDeadLockProfiler = new DeadLockProfiler();
		GMemory = new Memory();
		GSendBufferManager = new SendBufferManager();
		GDBConnectionPool = new DBConnectionPool();
		SocketUtils::Init();
	}

	~CoreGlobal()
	{
		delete GThreadManager;
		delete GDeadLockProfiler;
		delete GMemory;
		delete GSendBufferManager;
		delete GDBConnectionPool;
		SocketUtils::Clear();
	}
} GCoreGlobal;
