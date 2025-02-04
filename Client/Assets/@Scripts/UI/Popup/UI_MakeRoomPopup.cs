using Google.Protobuf.Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI_MakeRoomPopup : UI_Popup
{
    enum Buttons
    {
        MakeRoomButton,
        ExitButton,
    }

    enum InputFields
    {
        RoomNameInputField,
    }

    enum Texts
    {
        RoomNameEx,
    }

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Bind<Button>(typeof(Buttons));
        BindInputField(typeof(InputFields));
        BindText(typeof(Texts));

        Get<Button>((int)Buttons.MakeRoomButton).gameObject.BindEvent(ButtonEnterSound, Define.UIEvent.Enter);
        Get<Button>((int)Buttons.ExitButton).gameObject.BindEvent(ButtonEnterSound, Define.UIEvent.Enter);

        Get<Button>((int)Buttons.MakeRoomButton).gameObject.BindEvent(OnClickMakeRoomButton);
        Get<Button>((int)Buttons.ExitButton).gameObject.BindEvent(OnClickExitButton);

        return true;
    }

    void ButtonEnterSound()
    {
        Managers.Sound.Play(Define.Sound.Effect, "pt_in_rect");
    }
    void OnClickMakeRoomButton()
    {
        Managers.Sound.Play(Define.Sound.Effect, "click");
        string roomName = GetInputField((int)InputFields.RoomNameInputField).text;
        if(string.IsNullOrEmpty(roomName))
            roomName = GetText((int)Texts.RoomNameEx).text;

        C_MAKEROOM makeRoomPkt = new C_MAKEROOM();
        makeRoomPkt.RoomName = roomName;
        Managers.Net.SessionManager.Broadcast(makeRoomPkt);
    }
    void OnClickExitButton()
    {
        Managers.Sound.Play(Define.Sound.Effect, "click");
        ClosePopupUI();
    }
}
