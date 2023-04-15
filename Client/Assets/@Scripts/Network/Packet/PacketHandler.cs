﻿using Google.Protobuf;
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
        Managers.Game.Channels = pkt.Channels;
        Managers.Game.PlayerID = pkt.PlayerId;
    }

    public static void S_CHANNELCHOICEHandler(PacketSession session, IMessage packet)
    {
        ServerSession serverSession = session as ServerSession;
        S_CHANNELCHOICE pkt = packet as S_CHANNELCHOICE;

        if (pkt.Success == false)
        {
            Debug.Log($"실패 사유 : ");
            return;
        }

        Managers.Scene.ChangeScene<LobbyScene>(Define.SceneType.LobbyScene);
        Managers.Game.ChannelID = pkt.ChannelId;
        Managers.Game.Rooms = pkt.Rooms;
    }

    public static void S_CHANNELCHATHandler(PacketSession session, IMessage packet)
    {
        ServerSession serverSession = session as ServerSession;
        S_CHANNELCHAT pkt = packet as S_CHANNELCHAT;

        Managers.Game.LobbyUI.RecvChat(pkt.Name, pkt.Chat);
    }

    public static void S_MAKEROOMHandler(PacketSession session, IMessage packet)
    {
        ServerSession serverSession = session as ServerSession;
        S_MAKEROOM pkt = packet as S_MAKEROOM;

        if (pkt.Success == false)
            return;

        Managers.Game.Rooms = null;
        Managers.Game.LobbyUI = null;

        Managers.Game.Room = pkt.Room;

        Managers.Scene.ChangeScene<RoomScene>(Define.SceneType.RoomScene);
    }

    public static void S_CHANNELUPDATEHandler(PacketSession session, IMessage packet)
    {
        ServerSession serverSession = session as ServerSession;
        S_CHANNELUPDATE pkt = packet as S_CHANNELUPDATE;

        Managers.Game.Rooms = pkt.Rooms;
        Managers.Game.LobbyUI.RefreshLobbyPage();
    }

    public static void S_ROOMENTERHandler(PacketSession session, IMessage packet)
    {
        Debug.Log($"S_ROOMENTERHandler");
        ServerSession serverSession = session as ServerSession;
        S_ROOMENTER pkt = packet as S_ROOMENTER;

        if (pkt.Success == false)
            return;

        Managers.Game.Rooms = null;
        Managers.Game.LobbyUI = null;

        Managers.Game.Room = pkt.Room;
        Managers.Scene.ChangeScene<RoomScene>(Define.SceneType.RoomScene);
    }

    public static void S_ROOMUPDATEHandler(PacketSession session, IMessage packet)
    {
        Debug.Log($"S_ROOMUPDATEHandler");
        ServerSession serverSession = session as ServerSession;
        S_ROOMUPDATE pkt = packet as S_ROOMUPDATE;

        if (Managers.Game.Room.RoomId != pkt.Room.RoomId)
            return;

        Managers.Game.Rooms = null;
        Managers.Game.LobbyUI = null;

        Managers.Game.Room = pkt.Room;
        Managers.Game.RoomUI.RefreshRoomPage();
    }

    public static void S_ROOMSTARTHandler(PacketSession session, IMessage packet)
    {
        Debug.Log($"S_ROOMSTARTHandler");
        ServerSession serverSession = session as ServerSession;
        S_ROOMSTART pkt = packet as S_ROOMSTART;

        if (pkt.Success == false)
            return;

        Managers.Game.Room = pkt.Room;
        Managers.Scene.ChangeScene<GameScene>(Define.SceneType.GameScene);
    }

    public static void S_MOVEHandler(PacketSession session, IMessage packet)
    {

    }
}
