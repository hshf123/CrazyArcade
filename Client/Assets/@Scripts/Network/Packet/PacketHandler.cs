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

        Managers.Game.Channels = pkt.Channels;
        Managers.Game.PlayerID = pkt.Player.Id;
        Managers.Scene.ChangeScene<ChannelScene>(Define.SceneType.ChannelScene);
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

        Managers.Game.ChannelID = pkt.ChannelId;
        Managers.Game.Rooms = pkt.Rooms;
        Managers.Scene.ChangeScene<LobbyScene>(Define.SceneType.LobbyScene);
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

    public static void S_ROOMCHATHandler(PacketSession session, IMessage packet)
    {
        Debug.Log($"S_ROOMCHATHandler");
        ServerSession serverSession = session as ServerSession;
        S_ROOMCHAT pkt = packet as S_ROOMCHAT;

        Managers.Game.RoomUI.RecvChat(pkt.Player.Name, pkt.Msg);
    }

    public static void S_ROOMSTARTHandler(PacketSession session, IMessage packet)
    {
        Debug.Log($"S_ROOMSTARTHandler");
        ServerSession serverSession = session as ServerSession;
        S_ROOMSTART pkt = packet as S_ROOMSTART;

        if (pkt.Success == false)
            return;

        Managers.Game.Room = pkt.Room;
        Managers.Game.Spawn = pkt.Spawn;
        Managers.Scene.ChangeScene<GameScene>(Define.SceneType.GameScene);
    }

    public static void S_MOVEHandler(PacketSession session, IMessage packet)
    {
        Debug.Log($"S_MOVEHandler");
        ServerSession serverSession = session as ServerSession;
        S_MOVE pkt = packet as S_MOVE;

        long playerId = pkt.Player.Id;
        PlayerController pc = Managers.Object.FindPlayer(playerId);
        if (pc == null)
            return;
        
        // TODO : 내가 이상한 놈이면...?
        if (pc.PlayerInfo.Id == Managers.Object.MyPlayer.PlayerInfo.Id)
            return;

        // pkt.Force
        pc.WorldPos = new Vector3(pkt.PositionInfo.WorldPos.PosX, pkt.PositionInfo.WorldPos.PosY, 0);
        pc.CellPos = new Vector3Int(pkt.PositionInfo.CellPos.PosX, pkt.PositionInfo.CellPos.PosY, 0);
        pc.State = pkt.PositionInfo.State;
        pc.Dir = pkt.PositionInfo.MoveDir;
    }

    public static void S_BOMBHandler(PacketSession session, IMessage packet)
    {
        Debug.Log($"S_BOMBHandler");

        ServerSession serverSession = session as ServerSession;
        S_BOMB pkt = packet as S_BOMB;

        GameScene gameScene = Managers.Scene.CurrentScene as GameScene;
        if(gameScene == null)
        {
            Debug.Log($"{Managers.Scene.CurrentScene} is not GameScene");
            return;
        }
        gameScene.InstantiateBomb(pkt.Player, pkt.Cellpos, pkt.Player.Id);
    }

    public static void S_BOMBENDHandler(PacketSession session, IMessage packet)
    {
        Debug.Log($"S_BOMBENDHandler");

        ServerSession serverSession = session as ServerSession;
        S_BOMBEND pkt = packet as S_BOMBEND;

        Vector3Int bombCellPos = new Vector3Int(pkt.BombCellPos.PosX, pkt.BombCellPos.PosY, 0);
        BombController bc = Managers.Object.FindBomb(bombCellPos);
        if (bc == null)
            return;

        bc.Bomb(() =>
        {
            Managers.Object.RemoveBomb(bombCellPos);
        });

        // pkt.Player -> 물풍선 주인이 누군지
        foreach (PCellPos cellpos in pkt.DestroyObjectCellPoses)
            Managers.Map.Break(new Vector3Int(cellpos.PosX, cellpos.PosY, 0));
        foreach (PCellPos cellpos in pkt.DestroyItemCellPoses)
        {
            ItemController ic = Managers.Object.FindItem(new Vector3Int(cellpos.PosX, cellpos.PosY, 0));
            if (ic == null)
                continue;

            Managers.Resource.Destroy(ic.gameObject);
            Managers.Object.RemoveItem(new Vector3Int(cellpos.PosX, cellpos.PosY, 0));
        }
        foreach (var playerInfo in pkt.TrapPlayers)
        {
            PlayerController pc = Managers.Object.FindPlayer(playerInfo.Id);
            if (pc == null)
                continue;
            pc.State = PPlayerState.Intrap;
            pc.PlayerInfo = playerInfo;
        }
    }

    public static void S_ITEMSPAWNHandler(PacketSession session, IMessage packet)
    {
        Debug.Log($"S_ITEMSPAWNHandler");

        ServerSession serverSession = session as ServerSession;
        S_ITEMSPAWN pkt = packet as S_ITEMSPAWN;

        GameScene scene = Managers.Scene.CurrentScene as GameScene;
        if (scene == null)
            return;

        scene.InstantiateItem(new Vector3Int(pkt.CellPos.PosX, pkt.CellPos.PosY, 0), pkt.ItemType);
    }

    public static void S_DEADHandler(PacketSession session, IMessage packet)
    {
        Debug.Log($"S_DEADHandler");

        ServerSession serverSession = session as ServerSession;
        S_DEAD pkt = packet as S_DEAD;

        PlayerController pc = Managers.Object.FindPlayer(pkt.Player.Id);
        if (pc == null)
            return;

        pc.PlayerInfo = pkt.Player;
        pc.State = pkt.PosInfo.State;
        pc.OnDead();
    }

    public static void S_ITEMACQUISITIONHandler(PacketSession session, IMessage packet)
    {
        Debug.Log($"S_ITEMACQUISITIONHandler");

        ServerSession serverSession = session as ServerSession;
        S_ITEMACQUISITION pkt = packet as S_ITEMACQUISITION;

        PlayerController pc = Managers.Object.FindPlayer(pkt.PlayerInfo.Id);
        if (pc == null)
            return;
        
        pc.PlayerInfo = pkt.PlayerInfo;

        ItemController ic = Managers.Object.FindItem(new Vector3Int(pkt.ItemPos.PosX, pkt.ItemPos.PosY, 0));
        if (ic == null)
            return;

        Managers.Resource.Destroy(ic.gameObject);
        Managers.Object.RemoveItem(new Vector3Int(pkt.ItemPos.PosX, pkt.ItemPos.PosY, 0));
    }

    public static void S_GAMEENDHandler(PacketSession session, IMessage packet)
    {
        Debug.Log($"S_GAMEENDHandler");

        ServerSession serverSession = session as ServerSession;
        S_GAMEEND pkt = packet as S_GAMEEND;

        Managers.UI.ShowPopupUI<UI_GameResultPopup>(null, null,
            (popup) =>
            {
                var gameResultPopup = popup.GetComponent<UI_GameResultPopup>();
                gameResultPopup.EndInfo = pkt.EndInfo;
            });
    }
}
