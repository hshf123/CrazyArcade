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
        ExitButton,
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

        Bind<GameObject>(typeof(GameObjects));
        Bind<Button>(typeof(Buttons));
        BindInputField(typeof(InputFields));
        BindText(typeof(Texts));
        Bind<Image>(typeof(Images));
        
        Get<Button>((int)Buttons.ExitButton).gameObject.BindEvent(OnClickExitButton);
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

        RefreshRoom();

        return true;
    }

    public void RefreshRoom()
    {
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
        }
    }

    public void RecvChat(string name, string chat)
    {
        string msg = $"{name} : {chat}\n";
        GetText((int)Texts.ChatText).text += msg;
    }

    void OnClickStartButton()
    {

    }
    void OnClickReadyButton()
    {

    }
    void OnClickExitButton()
    {

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
