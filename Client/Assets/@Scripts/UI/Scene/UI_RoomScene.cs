using Google.Protobuf.Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SocialPlatforms.Impl;
using UnityEngine.UI;

public class UI_RoomScene : UI_Scene
{
    Dictionary<int, UI_PlayerSubItem> _playerList = new Dictionary<int, UI_PlayerSubItem>();

    enum GameObjects
    {
        Leader,
        Player_1,
        Player_2,
        Player_3,
        Player_4,
        Player_5,
        Player_6,
        Player_7,
    }
    enum Buttons
    {
        StartButton,
        ReadyButton,
        BackButton,
        ChatSendButton,

        Player_1Button,
        Player_2Button,
        Player_3Button,
        Player_4Button,
        Player_5Button,
        Player_6Button,
        Player_7Button,
    }
    enum InputFields
    {
        ChatInputField,
    }
    enum Texts
    {
        ChatText,
        MapNameText,
    }
    enum Images
    {
        MapIcon,
    }

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Managers.Game.RoomUI = this;
        Bind<GameObject>(typeof(GameObjects));
        Bind<Button>(typeof(Buttons));
        BindInputField(typeof(InputFields));
        BindText(typeof(Texts));
        Bind<Image>(typeof(Images));
        
        Get<Button>((int)Buttons.BackButton).gameObject.BindEvent(OnClickBackButton);
        Get<Button>((int)Buttons.ChatSendButton).gameObject.BindEvent(OnClickChatSendButton);

        Get<Button>((int)Buttons.Player_1Button).gameObject.BindEvent(OnClickBenButton1);
        Get<Button>((int)Buttons.Player_2Button).gameObject.BindEvent(OnClickBenButton2);
        Get<Button>((int)Buttons.Player_3Button).gameObject.BindEvent(OnClickBenButton3);
        Get<Button>((int)Buttons.Player_4Button).gameObject.BindEvent(OnClickBenButton4);
        Get<Button>((int)Buttons.Player_5Button).gameObject.BindEvent(OnClickBenButton5);
        Get<Button>((int)Buttons.Player_6Button).gameObject.BindEvent(OnClickBenButton6);
        Get<Button>((int)Buttons.Player_7Button).gameObject.BindEvent(OnClickBenButton7);

        if (Managers.Game.IsLeader)
        {
            Get<Button>((int)Buttons.StartButton).gameObject.BindEvent(OnClickStartButton);
            Get<Button>((int)Buttons.ReadyButton).gameObject.SetActive(false);
        }
        else
        {
            Get<Button>((int)Buttons.ReadyButton).gameObject.BindEvent(OnClickReadyButton);
            Get<Button>((int)Buttons.StartButton).gameObject.SetActive(false);
        }

        GetText((int)Texts.ChatText).text = "안내 : RoomScene입니다.\n";

        RefreshRoomPage();

        return true;
    }
    void Update()
    {
        if (GetInputField((int)InputFields.ChatInputField).isFocused && Input.GetKey(KeyCode.KeypadEnter))
            OnClickChatSendButton();
    }

    public void RefreshRoomPage()
    {
        foreach(var player in _playerList.Values)
        {
            Managers.Resource.Destroy(player.gameObject);
        }
        _playerList.Clear();

        for (int i = 1; i < 8; i++)
        {
            bool ben = Managers.Game.Room.BenList[i];
            string playerPos = $"Player_{i}";
            if (ben == false)
            {
                gameObject.FindChild(playerPos, true).FindChild("ben").SetActive(false);
            }
            gameObject.FindChild(playerPos, true).FindChild("ready").SetActive(false);
        }

        foreach (var player in Managers.Game.Room.PlayerList)
        {
            string playerPos = $"Player_{player.RoomIdx}";
            if (playerPos.Equals("Player_0"))
            {
                playerPos = "Leader";
            }

            Managers.UI.MakeSubItem<UI_PlayerSubItem>(gameObject.FindChild(playerPos, true).transform, null,
                (subItem)=>
                {
                    subItem.SetPlayerName(player.Name);
                    subItem.SetPlayerLevel(player.Level);
                    _playerList.Add(player.RoomIdx, subItem);
                });

            if(player.Ready)
                gameObject.FindChild(playerPos, true).FindChild("ready").SetActive(true);
        }
    }

    public void RecvChat(string name, string chat)
    {
        string msg = $"{name} : {chat}\n";
        GetText((int)Texts.ChatText).text += msg;
    }

    void OnClickStartButton()
    {
        C_ROOMSTART roomStartPkt = new C_ROOMSTART();
        roomStartPkt.PlayerId = Managers.Game.PlayerID;
        roomStartPkt.ChannelId = Managers.Game.ChannelID;
        roomStartPkt.RoomId = Managers.Game.Room.RoomId;
        Managers.Net.SessionManager.Broadcast(roomStartPkt);
    }
    void OnClickReadyButton()
    {
        C_ROOMREADY roomReadyPkt = new C_ROOMREADY();
        roomReadyPkt.PlayerId = Managers.Game.PlayerID;
        roomReadyPkt.ChannelId = Managers.Game.ChannelID;
        roomReadyPkt.RoomId = Managers.Game.Room.RoomId;
        Managers.Net.SessionManager.Broadcast(roomReadyPkt);
    }
    void OnClickBackButton()
    {

    }
    void OnClickChatSendButton()
    {

    }
    void OnClickBenButton(int n)
    {
        if (Managers.Game.IsLeader == false)
            return;
    }
    void OnClickBenButton1()
    {
        OnClickBenButton(1);
    }
    void OnClickBenButton2() 
    {
        OnClickBenButton(2);
    }
    void OnClickBenButton3() 
    {
        OnClickBenButton(3);
    }
    void OnClickBenButton4() 
    {
        OnClickBenButton(4);
    }
    void OnClickBenButton5() 
    {
        OnClickBenButton(5);
    }
    void OnClickBenButton6() 
    {
        OnClickBenButton(6);
    }
    void OnClickBenButton7()
    {
        OnClickBenButton(7);
    }
}
