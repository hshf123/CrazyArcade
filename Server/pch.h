#pragma once

#define WIN32_LEAN_AND_MEAN // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#ifdef _DEBUG
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#endif

#include "CorePch.h"
#include "Struct.pb.h"
#include "DBConnection.h"
#include "DBConnectionPool.h"
#include "DBBind.h"

using ClientSessionRef = shared_ptr<class ClientSession>;
using ClientSessionWeakRef = weak_ptr<class ClientSession>;
using PlayerRef = shared_ptr<class Player>;
using PlayerWeakRef = weak_ptr<class Player>;
