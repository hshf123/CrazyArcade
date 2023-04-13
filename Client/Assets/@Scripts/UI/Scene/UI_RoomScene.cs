using Google.Protobuf.Collections;
using Google.Protobuf.Protocol;
using Protocol;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UI;

public class UI_RoomScene : UI_Scene
{
    // 채팅 패킷은 오면 바로 띄우면 되고, 내가 들어오기전에 대화했던 내용은 표시할 필요가 없다...
    // 방은 6개 단위로 표현

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

    RepeatedField<Room> _rooms = new RepeatedField<Room>();
    int _roomPage = 0;

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Managers.Game.Room = this;
        Bind<GameObject>(typeof(GameObjects));
        Bind<Button>(typeof(Buttons));
        BindInputField(typeof(InputFields));
        BindText(typeof(Texts));

        RoomInfo roominfo = Managers.Game.RoomInfo;
        _rooms = roominfo.Rooms;

        Get<Button>((int)Buttons.ChatSendButton).gameObject.BindEvent(OnClickChatSendButton);
        Get<Button>((int)Buttons.RightButton).gameObject.BindEvent(OnClickRightButton);
        Get<Button>((int)Buttons.LeftButton).gameObject.BindEvent(OnClickLeftButton);
        GetText((int)Texts.ChatText).text = "안내 : 본 게임은 크아 모작임\n";

        RefreshRoomPage();

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

    void RefreshRoomPage()
    {
        ClearRoomPage();

        for (int i = _roomPage * 6; i < (_roomPage + 1) * 6; i++)
        {
            if (i >= _rooms.Count)
            {
                Managers.UI.MakeSubItem<UI_RoomDummySubItem>(Get<GameObject>((int)GameObjects.RoomList).transform);
            }
            else
            {
                Managers.UI.MakeSubItem<UI_RoomSubItem>(Get<GameObject>((int)GameObjects.RoomList).transform);
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
        int maxPageCount = _rooms.Count / 6;
        _roomPage = Mathf.Min(_roomPage + 1, maxPageCount);
    }

    void OnClickLeftButton()
    {
        _roomPage = Mathf.Max(_roomPage - 1, 0);
    }
}
