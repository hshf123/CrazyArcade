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

        Managers.Scene.ChangeScene<RoomScene>(Define.SceneType.RoomScene);
        Managers.Game.ChannelID = pkt.ChannelId;
        Managers.Game.RoomInfo = pkt.RoomInfo;
    }

    public static void S_CHANNELCHATHandler(PacketSession session, IMessage packet)
    {
        ServerSession serverSession = session as ServerSession;
        S_CHANNELCHAT pkt = packet as S_CHANNELCHAT;

        Managers.Game.Room.RecvChat(pkt.Name, pkt.Chat);
    }

    public static void S_MAKEROOMHandler(PacketSession session, IMessage packet)
    {

    }

    public static void S_ROOMCHATHandler(PacketSession session, IMessage packet)
    {

    }
}
