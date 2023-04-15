using Google.Protobuf.Collections;
using Google.Protobuf.Protocol;
using Protocol;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public class UI_LobbyScene : UI_Scene
{
    List<int> _roomIds = new List<int>();
    List<string> _roomNames = new List<string>();
    List<int> _roomCurrentPlayerCounts = new List<int>();
    List<int> _roomMaxCurrentPlayerCounts = new List<int>();

    enum GameObjects
    {
        RoomList,
    }

    enum Buttons
    {
        MakeRoomButton,
        RightButton,
        LeftButton,
        ChatSendButton,
    }

    enum InputFields
    {
        ChatInputField,
    }

    enum Texts
    {
        ChatText,
    }

    int _roomPage = 0;

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Managers.Game.Lobby = this;
        Bind<GameObject>(typeof(GameObjects));
        Bind<Button>(typeof(Buttons));
        BindInputField(typeof(InputFields));
        BindText(typeof(Texts));

        Get<Button>((int)Buttons.ChatSendButton).gameObject.BindEvent(OnClickChatSendButton);
        Get<Button>((int)Buttons.RightButton).gameObject.BindEvent(OnClickRightButton);
        Get<Button>((int)Buttons.LeftButton).gameObject.BindEvent(OnClickLeftButton);
        Get<Button>((int)Buttons.MakeRoomButton).gameObject.BindEvent(OnClickMakeRoomButton);
        GetText((int)Texts.ChatText).text = "안내 : 본 게임은 크아 모작임\n";

        RefreshLobbyPage();

        return true;
    }

    void Update()
    {
        if(GetInputField((int)InputFields.ChatInputField).isFocused && Input.GetKey(KeyCode.Return))
            OnClickChatSendButton();
    }

    public void RecvChat(string name, string chat)
    {
        string msg = $"{name} : {chat}\n";
        GetText((int)Texts.ChatText).text += msg;
    }

    public void RefreshLobbyPage()
    {
        ClearRoomPage();

        _roomIds.Clear();
        _roomNames.Clear();
        _roomCurrentPlayerCounts.Clear();
        _roomMaxCurrentPlayerCounts.Clear();
        int idx = 0;
        for (int i = _roomPage * 6; i < (_roomPage + 1) * 6; i++)
        {
            if (i >= Managers.Game.LobbyInfo.RoomCount)
            {
                Managers.UI.MakeSubItem<UI_RoomDummySubItem>(Get<GameObject>((int)GameObjects.RoomList).transform);
            }
            else
            {
                _roomIds.Add(Managers.Game.LobbyInfo.Rooms[i].RoomId);
                _roomNames.Add(Managers.Game.LobbyInfo.Rooms[i].RoomName);
                _roomCurrentPlayerCounts.Add(Managers.Game.LobbyInfo.Rooms[i].CurrentPlayerCount);
                _roomMaxCurrentPlayerCounts.Add(Managers.Game.LobbyInfo.Rooms[i].MaxPlayerCount);
                Managers.UI.MakeSubItem<UI_RoomSubItem>(Get<GameObject>((int)GameObjects.RoomList).transform, null,
                    (room)=>
                    {
                        room.gameObject.BindEvent(OnClickRoom);
                        room.RoomID = _roomIds[idx];
                        room.RoomName = _roomNames[idx];
                        room.CurrentPlayerCount = _roomCurrentPlayerCounts[idx];
                        room.MaxPlayerCount = _roomMaxCurrentPlayerCounts[idx++];
                        // room.RoomState;
                    });
            }
        }
    }
    void ClearRoomPage()
    {
        UI_Base[] childs = Utils.FindChilds<UI_Base>(Get<GameObject>((int)GameObjects.RoomList), false);
        foreach (UI_Base child in childs)
        {
            Managers.Resource.Destroy(child.gameObject);
        }
    }

    void OnClickMakeRoomButton()
    {
        Managers.UI.ShowPopupUI<UI_MakeRoomPopup>();
    }
    void OnClickChatSendButton()
    {
        string msg = GetInputField((int)InputFields.ChatInputField).text;
        if (string.IsNullOrEmpty(msg))
            return;

        C_CHANNELCHAT chatPkt = new C_CHANNELCHAT();
        chatPkt.ChannelId = Managers.Game.ChannelID;
        chatPkt.PlayerId = Managers.Game.PlayerID;
        chatPkt.Chat = msg;
        GetInputField((int)InputFields.ChatInputField).text = "";
        Managers.Net.SessionManager.Broadcast(chatPkt);
    }
    void OnClickRightButton()
    {
        int maxPageCount = Managers.Game.LobbyInfo.RoomCount / 6;
        _roomPage = Mathf.Min(_roomPage + 1, maxPageCount);
        RefreshLobbyPage();
    }
    void OnClickLeftButton()
    {
        _roomPage = Mathf.Max(_roomPage - 1, 0);
        RefreshLobbyPage();
    }
    void OnClickRoom(PointerEventData evtData)
    {
        GameObject go = evtData.pointerCurrentRaycast.gameObject;
        if (go == null)
            return;

        UI_RoomSubItem room = go.GetComponent<UI_RoomSubItem>();
        Debug.Log($"{room.RoomID}번 방에 들어가려고 시도!");

        C_ROOMENTER roomEnterPkt = new C_ROOMENTER();
        roomEnterPkt.ChannelId = Managers.Game.ChannelID;
        roomEnterPkt.PlayerId = Managers.Game.PlayerID;
        roomEnterPkt.RoomId = room.RoomID;
        Managers.Net.SessionManager.Broadcast(roomEnterPkt);
    }
}
