#include "pch.h"
#include "ClientPacketHandler.h"
#include "ClientSession.h"
#include "Player.h"
#include "Protocol.pb.h"
#include "ClientSessionManager.h"
#include "Managers.h"
#include "ChannelManager.h"
#include "Channel.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

	return false;
}

bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt)
{
	ClientSessionRef clientSession = static_pointer_cast<ClientSession>(session);
	wstring id = Utils::ConvertStringToWString(pkt.id());
	wstring pw = Utils::ConvertStringToWString(pkt.pw());

	{
		// 사용자 정보 불러오기
		DBConnection* dbConn = GDBConnectionPool->Pop();
		auto query = L"SELECT *							\
						FROM [dbo].[UserInfo]			\
						WHERE id = (?)";

		DBBind<1, 2> dbBind(*dbConn, query);

		dbBind.BindParam(0, id.c_str());

		WCHAR outID[50];
		WCHAR outPW[50];
		dbBind.BindCol(0, OUT outID);
		dbBind.BindCol(1, OUT outPW);

		ASSERT_CRASH(dbBind.Execute());
		dbConn->Fetch();
		GDBConnectionPool->Push(dbConn);

		if (id != outID)
		{
			wcout.imbue(locale("kor"));
			wcout << id << L" " << L"로그인 실패! 존재하지 않는 아이디" << endl;
			return false;
		}
		if (pw != outPW)
		{
			wcout.imbue(locale("kor"));
			wcout << pw << L" " << L"로그인 실패! 패스워드 불일치" << endl;
			return false;
		}
	}

	wcout.imbue(locale("kor"));
	wcout << L"로그인 성공!" << endl;

	{
		// TODO : 정보가 없으면 새로 만들기
		// 유저 정보 불러오기
		DBConnection* dbConn = GDBConnectionPool->Pop();
		auto query = L"SELECT *							\
						FROM [dbo].[Player]				\
						WHERE player_id = (?)";

		DBBind<1, 4> dbBind(*dbConn, query);

		dbBind.BindParam(0, id.c_str());

		WCHAR outName[50];
		WCHAR outPlayerID[50];
		int32 level;
		float exp;
		dbBind.BindCol(0, OUT outName);
		dbBind.BindCol(1, OUT outPlayerID);
		dbBind.BindCol(2, OUT level);
		dbBind.BindCol(3, OUT exp);

		ASSERT_CRASH(dbBind.Execute());
		dbConn->Fetch();
		GDBConnectionPool->Push(dbConn);

		PlayerRef player = MakeShared<Player>(
			clientSession,
			outName,
			outPlayerID,
			level,
			exp,
			Managers::GetInstance()->GenerateID(outPlayerID)
		);
		clientSession->MyPlayer = player;
		ChannelManager::GetInstance()->AddPlayer(player);
	}

	Protocol::S_LOGIN loginPkt;
	loginPkt.set_success(true);
	Protocol::ChannelInfo* channelInfo = new Protocol::ChannelInfo();
	ChannelManager::GetInstance()->FillChannelInfo(channelInfo);
	loginPkt.set_allocated_channelinfo(channelInfo);
	loginPkt.set_playerid(clientSession->MyPlayer.lock()->GetId());
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(loginPkt);
	clientSession->Send(sendBuffer);

	return true;
}

bool Handle_C_CHANNELCHOIC(PacketSessionRef& session, Protocol::C_CHANNELCHOIC& pkt)
{
	// success false, 입장가능한지 체크
	ClientSessionRef clientSession = static_pointer_cast<ClientSession>(session);

	PlayerRef player = ChannelManager::GetInstance()->FindPlayer(pkt.playerid());
	if (player == nullptr)
		return false;

	ChannelRef channel = ChannelManager::GetInstance()->FindChannel(pkt.channelid());
	if (channel == nullptr)
		return false;

	channel->InsertPlayer(player);
	ChannelManager::GetInstance()->RemovePlayer(pkt.playerid());

	Protocol::S_CHANNELCHOIC channelChoicePkt;
	channelChoicePkt.set_success(true);
	channelChoicePkt.set_channelid(channel->GetId());
	Protocol::RoomInfo* roomInfo = new Protocol::RoomInfo();
	channel->FillRoomInfo(roomInfo);
	channelChoicePkt.set_allocated_roominfo(roomInfo);

	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(channelChoicePkt);
	clientSession->Send(sendBuffer);

	return true;
}

bool Handle_C_MAKEROOM(PacketSessionRef& session, Protocol::C_MAKEROOM& pkt)
{
	ClientSessionRef clientSession = static_pointer_cast<ClientSession>(session);

	ChannelRef channel = ChannelManager::GetInstance()->FindChannel(pkt.channelid());
	if (channel == nullptr)
		return false;

	return true;
}
