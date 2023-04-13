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

        Get<Button>((int)Buttons.MakeRoomButton).gameObject.BindEvent(OnClickMakeRoomButton);

        return true;
    }

    void OnClickMakeRoomButton()
    {
        string roomName = GetInputField((int)InputFields.RoomNameInputField).text;
        if(string.IsNullOrEmpty(roomName))
            roomName = GetText((int)Texts.RoomNameEx).text;

        C_MAKEROOM makeRoomPkt = new C_MAKEROOM();
        makeRoomPkt.RoomName = roomName;
        makeRoomPkt.PlayerId = Managers.Game.PlayerID;
        makeRoomPkt.ChannelId = Managers.Game.ChannelID;
        Managers.Net.SessionManager.Broadcast(makeRoomPkt);
    }
}
