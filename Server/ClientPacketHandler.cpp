#include "pch.h"
#include "ClientPacketHandler.h"
#include "ClientSession.h"
#include "Player.h"
#include "Protocol.pb.h"
#include "ClientSessionManager.h"
#include "Managers.h"
#include "ChannelManager.h"
#include "Channel.h"
#include "Room.h"

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

	{
		wstringstream log;
		log << L"LOGIN : " << id;
		Utils::Log(log);
	}

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

		PlayerRef player = MakeShared<Player>();
		player->PlayerInfo.set_playerid(Utils::ConvertWStringToString(outPlayerID));
		player->PlayerInfo.set_name(Utils::ConvertWStringToString(outName));
		player->PlayerInfo.set_level(level);
		player->PlayerInfo.set_exp(exp);
		player->PlayerInfo.set_id(Managers::GetInstance()->GenerateID(outName));
		player->PlayerInfo.set_channelid(-1);
		player->PlayerInfo.set_roomid(-1);
		player->PlayerInfo.set_roomidx(-1);
		player->PlayerInfo.set_ready(false);
		player->PlayerInfo.set_speed(2.f);
		player->PlayerInfo.set_maxbombcount(1);
		player->PlayerInfo.set_bombcount(0);
		player->PlayerInfo.set_bombrange(1);

		clientSession->MyPlayer = player;
		player->SetClientSession(clientSession);
		ChannelManager::GetInstance()->AddPlayer(player);

		wstringstream log;
		log << L"ENTER NEW PLAYER / ID : " << player->PlayerInfo.id();
		Utils::Log(log);
	}

	Protocol::S_LOGIN loginPkt;
	loginPkt.set_success(true);
	for (Protocol::PChannel c : ChannelManager::GetInstance()->GetChannelsProtocol())
	{
		Protocol::PChannel* channel = loginPkt.add_channels();
		channel->CopyFrom(c);
	}
	loginPkt.set_allocated_player(clientSession->MyPlayer->GetPlayerProtocol());
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(loginPkt);
	clientSession->Send(sendBuffer);

	return true;
}

bool Handle_C_CHANNELCHOICE(PacketSessionRef& session, Protocol::C_CHANNELCHOICE& pkt)
{
	// success false, 입장가능한지 체크
	ClientSessionRef clientSession = static_pointer_cast<ClientSession>(session);
	PlayerRef player = clientSession->MyPlayer;
	if (player == nullptr)
		return false;

	ChannelRef channel = ChannelManager::GetInstance()->FindChannel(pkt.channelid());
	if (channel == nullptr)
		return false;

	channel->InsertPlayer(player);
	ChannelManager::GetInstance()->RemovePlayer(player->PlayerInfo.id());

	return true;
}

bool Handle_C_CHANNELCHAT(PacketSessionRef& session, Protocol::C_CHANNELCHAT& pkt)
{
	wstringstream log;
	ClientSessionRef clientSession = static_pointer_cast<ClientSession>(session);

	PlayerRef player = clientSession->MyPlayer;
	if (player == nullptr)
		return false;

	ChannelRef channel = ChannelManager::GetInstance()->FindChannel(player->PlayerInfo.channelid());
	if (channel == nullptr)
		return false;

	log << "PLAYER ID : " << player->PlayerInfo.id() << L" SEND CHAT MESSAGE CHANNEL ID : " << channel->ChannelInfo.channelid();

	Protocol::S_CHANNELCHAT chatPkt;
	chatPkt.set_name(player->PlayerInfo.name());
	chatPkt.set_chat(pkt.chat());
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(chatPkt);
	channel->Broadcast(sendBuffer);

	Utils::Log(log);

	return true;
}

bool Handle_C_MAKEROOM(PacketSessionRef& session, Protocol::C_MAKEROOM& pkt)
{
	ClientSessionRef clientSession = static_pointer_cast<ClientSession>(session);
	PlayerRef player = clientSession->MyPlayer;
	if (player == nullptr)
		return false;

	ChannelRef channel = ChannelManager::GetInstance()->FindChannel(player->PlayerInfo.channelid());
	if (channel == nullptr)
		return false;

	channel->AddRoom(player->PlayerInfo.id(), pkt.roomname());

	return true;
}

bool Handle_C_ROOMENTER(PacketSessionRef& session, Protocol::C_ROOMENTER& pkt)
{
	ClientSessionRef clientSession = static_pointer_cast<ClientSession>(session);
	PlayerRef player = clientSession->MyPlayer;
	if (player == nullptr)
		return false;

	wstringstream log;

	ChannelRef channel = ChannelManager::GetInstance()->FindChannel(player->PlayerInfo.channelid());
	if (channel == nullptr)
		return false;

	log << L"PLYAER ID : " << player->PlayerInfo.id() << L" ENTER ROOM, ROOM ID : ";

	RoomRef room = player->GetRoom();
	if (room == nullptr)
		return false;

	log << room->GetId();

	room->InsertPlayer(player);
	channel->RemovePlayer(player->PlayerInfo.id());

	{
		// 입장한 사용자한테 방정보 전송
		Protocol::S_ROOMENTER roomEnterPkt;
		roomEnterPkt.set_success(true);
		roomEnterPkt.set_allocated_room(room->GetRoomProtocol());
		SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(roomEnterPkt);
		clientSession->Send(sendBuffer);
	}

	{
		// 입장한 방에 broadcast, 입장한 사용자는 제외하고
		Protocol::S_ROOMUPDATE roomUpdatePkt;
		roomUpdatePkt.set_allocated_room(room->GetRoomProtocol());
		SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(roomUpdatePkt);
		room->Broadcast(sendBuffer, clientSession);
	}

	{
		// 해당 채널 로비에 broadcast
		Protocol::S_CHANNELUPDATE channelUpdatePkt;
		for (Protocol::PRoom r : channel->GetRoomsProtocol())
		{
			Protocol::PRoom* room = channelUpdatePkt.add_rooms();
			room->CopyFrom(r);
		}
		SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(channelUpdatePkt);
		channel->Broadcast(sendBuffer);
	}

	Utils::Log(log);

	return true;
}

bool Handle_C_ROOMLEAVE(PacketSessionRef& session, Protocol::C_ROOMLEAVE& pkt)
{
	ClientSessionRef clientSession = static_pointer_cast<ClientSession>(session);

	PlayerRef player = clientSession->MyPlayer;
	if (player == nullptr)
		return false;

	RoomRef room = player->GetRoom();
	if (room == nullptr)
		return false;

	room->RemovePlayer(player->PlayerInfo.id());
	return true;
}

bool Handle_C_ROOMREADY(PacketSessionRef& session, Protocol::C_ROOMREADY& pkt)
{
	ClientSessionRef clientSession = static_pointer_cast<ClientSession>(session);
	PlayerRef player = clientSession->MyPlayer;
	if (player == nullptr)
		return false;

	wstringstream log;
	
	log << L"PLAYER ID : " << player->PlayerInfo.id() << L"SET READY : ";

	RoomRef room = player->GetRoom();
	if (room == nullptr)
		return false;

	player->PlayerInfo.set_ready(!player->PlayerInfo.ready());
	Protocol::S_ROOMUPDATE roomUpdatePkt;
	roomUpdatePkt.set_allocated_room(room->GetRoomProtocol());
	room->Broadcast(roomUpdatePkt);

	log << (player->PlayerInfo.ready() ? L"READY" : L"NONREADY");
	Utils::Log(log);

	return true;
}

bool Handle_C_ROOMCHAT(PacketSessionRef& session, Protocol::C_ROOMCHAT& pkt)
{
	ClientSessionRef clientSession = static_pointer_cast<ClientSession>(session);
	PlayerRef player = clientSession->MyPlayer;
	if (player == nullptr)
		return false;

	RoomRef room = player->GetRoom();
	if (room == nullptr)
		return false;

	room->HandleChat(player, pkt);

	return true;
}

bool Handle_C_ROOMSTART(PacketSessionRef& session, Protocol::C_ROOMSTART& pkt)
{
	ClientSessionRef clientSession = static_pointer_cast<ClientSession>(session);
	wstringstream log;
	PlayerRef player = clientSession->MyPlayer;
	if (player == nullptr)
		return false;

	log << L"PLAYER ID : " << player->PlayerInfo.id() << L"ROOM START, ";

	RoomRef room = player->GetRoom();
	if (room == nullptr)
		return false;

	if (room->CanGameStart() == false)
		return false;

	log << L"ROOM ID : " << room->GetId() << L" START";
	Utils::Log(log);

	return true;
}

bool Handle_C_MOVE(PacketSessionRef& session, Protocol::C_MOVE& pkt)
{
	ClientSessionRef clientSession = static_pointer_cast<ClientSession>(session);

	PlayerRef player = clientSession->MyPlayer;
	if (player == nullptr)
		return false;

	ChannelRef channel = ChannelManager::GetInstance()->FindChannel(player->PlayerInfo.channelid());
	if (channel == nullptr)
		return false;

	RoomRef room = channel->FindRoom(player->PlayerInfo.roomid());
	if (room == nullptr)
		return false;

	room->HandleMove(player, pkt);

	return true;
}

bool Handle_C_BOMB(PacketSessionRef& session, Protocol::C_BOMB& pkt)
{
	ClientSessionRef clientSession = static_pointer_cast<ClientSession>(session);

	PlayerRef player = clientSession->MyPlayer;
	if (player == nullptr)
		return false;

	ChannelRef channel = ChannelManager::GetInstance()->FindChannel(player->PlayerInfo.channelid());
	if (channel == nullptr)
		return false;

	RoomRef room = channel->FindRoom(player->PlayerInfo.roomid());
	if (room == nullptr)
		return false;

	room->HandleBomb(player, pkt);
	return true;
}
