#include "pch.h"
#include "CorePch.h"
#include "ThreadManager.h"

#include "Service.h"
#include "ClientSession.h"
#include "SendBuffer.h"
#include "ClientSessionManager.h"
#include "ClientPacketHandler.h"
#include "Protocol.pb.h"
#include "DBConnectionPool.h"
#include "DBBind.h"
#include "ChannelManager.h"

void MakeTestData(int32 idx)
{
	{
		DBConnection* dbConn = GDBConnectionPool->Pop();
		auto query = L"INSERT INTO [dbo].[UserInfo]			\
						([id], [password])					\
						VALUES (?, ?)";
		DBBind<2, 0> dbBind(*dbConn, query);

		{
			wstringstream ss;
			ss << L"test" << idx;
			WCHAR id[20];
			::memset(id, 0, sizeof(id));
			::memcpy(id, ss.str().c_str(), ss.str().size() * sizeof(WCHAR));
 			dbBind.BindParam(0, id);
		}
		{
			wstringstream ss;
			ss << L"test" << idx;
			WCHAR password[20];
			::memset(password, 0, sizeof(password));
			::memcpy(password, ss.str().c_str(), ss.str().size() * sizeof(WCHAR));
			dbBind.BindParam(1, password);
		}

		ASSERT_CRASH(dbBind.Execute());
		GDBConnectionPool->Push(dbConn);
	}
	{
		DBConnection* dbConn = GDBConnectionPool->Pop();
		auto query = L"INSERT INTO [dbo].[Player]				\
						([name], [player_id], [level], [exp])	\
						VALUES (?, ?, ?, ?)";
		DBBind<4, 0> dbBind(*dbConn, query);
		{
			wstringstream ss;
			ss << L"TestPlayer" << idx;
			WCHAR name[20];
			::memset(name, 0, sizeof(name));
			::memcpy(name, ss.str().c_str(), ss.str().size() * sizeof(WCHAR));
			dbBind.BindParam(0, name);
		}
		{
			wstringstream ss;
			ss << L"test" << idx;
			WCHAR player_id[20];
			::memset(player_id, 0, sizeof(player_id));
			::memcpy(player_id, ss.str().c_str(), ss.str().size() * sizeof(WCHAR));
			dbBind.BindParam(1, player_id);
		}
		int32 level = 1;
		float exp = 0.f;
		dbBind.BindParam(2, level);
		dbBind.BindParam(3, exp);

		ASSERT_CRASH(dbBind.Execute());
		GDBConnectionPool->Push(dbConn);
	}
}

int main()
{
	// ASSERT_CRASH(GDBConnectionPool->Connect(1, L"Driver={ODBC Driver 18 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=ServerDB;Trusted_Connection=Yes;"));
	ASSERT_CRASH(GDBConnectionPool->Connect(10, L"Driver={ODBC Driver 17 for SQL Server};Server=SANGHYUN\\SQLEXPRESS;Database=CrazyArcadeDB;Trusted_Connection=Yes;"));
	{
		// FOREIGN KEY 제약 조건 삭제
		auto query1 = L"IF EXISTS (SELECT * FROM sys.foreign_keys WHERE name = 'FK_Player_UserInfo') \
                   ALTER TABLE [dbo].[Player] DROP CONSTRAINT [FK_Player_UserInfo];";
		DBConnection* dbConn1 = GDBConnectionPool->Pop();
		ASSERT_CRASH(dbConn1->Execute(query1));
		GDBConnectionPool->Push(dbConn1);

		// 테이블 삭제
		auto query2 = L"DROP TABLE IF EXISTS [dbo].[Player];";
		DBConnection* dbConn2 = GDBConnectionPool->Pop();
		ASSERT_CRASH(dbConn2->Execute(query2));
		GDBConnectionPool->Push(dbConn2);
	}
	{
		auto query = L"														\
			DROP TABLE IF EXISTS [dbo].[UserInfo];							\
			DROP TABLE IF EXISTS [dbo].[Player];							\
			CREATE TABLE [dbo].[UserInfo]									\
			(																\
				[id] NVARCHAR(15) NOT NULL PRIMARY KEY,						\
				[password] NVARCHAR(15) NOT NULL							\
			);																\
																			\
			CREATE TABLE [dbo].[Player]										\
			(																\
				[name] NVARCHAR(20) NOT NULL PRIMARY KEY,					\
				[player_id] NVARCHAR(15) NOT NULL,							\
				[level] INT NOT NULL,										\
				[exp] FLOAT NOT NULL,										\
				FOREIGN KEY (player_id) REFERENCES UserInfo(id)				\
			);																\
			";
	
		DBConnection* dbConn = GDBConnectionPool->Pop();
		ASSERT_CRASH(dbConn->Execute(query));
		GDBConnectionPool->Push(dbConn);
	}

#pragma region Test Data
	for (int32 i = 0; i < 20; i++)
	{
		MakeTestData(i + 1);
	}
#pragma endregion

	ClientPacketHandler::Init();

	for (int i = 0; i < 5; i++)
	{
		ChannelManager::GetInstance()->AddChannel(10);
	}

	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ClientSession>,
		100);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 10; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}
	for (int32 i = 0; i < 2; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					ChannelManager::GetInstance()->Update();

					this_thread::sleep_for(1ms);
				}
			});
	}

	GThreadManager->Join();
}