using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI_RoomScene : UI_Scene
{
    bool[] _ben = new bool[8];


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

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Bind<Button>(typeof(Buttons));
        BindInputField(typeof(InputFields));
        BindText(typeof(Texts));
        
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

        return true;
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
        _ben[n] = !_ben[n];
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
