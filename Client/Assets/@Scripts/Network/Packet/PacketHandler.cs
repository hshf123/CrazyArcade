using Google.Protobuf;
using Google.Protobuf.Protocol;
using Protocol;
using System;
using System.Net;
using UnityEngine;

public class PacketHandler
{
    public static void S_LOGINHandler(PacketSession session, IMessage packet)
    {
        ServerSession serverSession = session as ServerSession;
        S_LOGIN pkt = packet as S_LOGIN;

        if (pkt.Success == false)
        {
            Debug.Log($"실패 사유 : ");
            return;
        }

        Managers.Scene.ChangeScene<ChannelScene>(Define.SceneType.ChannelScene);
        Managers.Game.ChannelInfo = pkt.ChannelInfo;
        Managers.Game.PlayerID = pkt.PlayerId;
    }

    public static void S_CHANNELCHOICHandler(PacketSession session, IMessage packet)
    {
        ServerSession serverSession = session as ServerSession;
        S_CHANNELCHOIC pkt = packet as S_CHANNELCHOIC;
        
        if(pkt.Success == false)
        {
            Debug.Log($"실패 사유 : ");
            return;
        }

        Managers.Scene.ChangeScene<LobbyScene>(Define.SceneType.LobbyScene);
        Managers.Game.ChannelID = pkt.ChannelId;
        Managers.Game.LobbyInfo = pkt.LobbyInfo;
    }

    public static void S_CHANNELCHATHandler(PacketSession session, IMessage packet)
    {
        ServerSession serverSession = session as ServerSession;
        S_CHANNELCHAT pkt = packet as S_CHANNELCHAT;

        Managers.Game.Lobby.RecvChat(pkt.Name, pkt.Chat);
    }

    public static void S_MAKEROOMHandler(PacketSession session, IMessage packet)
    {
        ServerSession serverSession = session as ServerSession;
        S_MAKEROOM pkt = packet as S_MAKEROOM;

        if (pkt.Success == false)
            return;

        Managers.Game.RoomID = pkt.RoomId;

        // TODO : RoomScene
    }

    public static void S_CHANNELUPDATEHandler(PacketSession session, IMessage packet)
    {
        ServerSession serverSession = session as ServerSession;
        S_CHANNELUPDATE pkt = packet as S_CHANNELUPDATE;

        Managers.Game.LobbyInfo = pkt.LobbyInfo;
        Managers.Game.Lobby.RefreshRoomPage();
    }
}
