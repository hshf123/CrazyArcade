using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UI_RoomSubItem : UI_Base
{
    public int RoomID { get; set; }

    enum Texts
    {
        RoomNameText,
        RoomNumberText,
        RoomPlayerCountText,
        RoomStateText,
    }

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        BindText(typeof(Texts));

        GetText((int)Texts.RoomNameText).text = Managers.Game.RoomInfo.Room.RoomName;
        GetText((int)Texts.RoomNumberText).text = $"{Managers.Game.RoomInfo.Room.RoomId:D2}";
        GetText((int)Texts.RoomPlayerCountText).text = $"{Managers.Game.RoomInfo.Room.CurrentPlayerCount}/{Managers.Game.RoomInfo.Room.MaxPlayerCount}";
        GetText((int)Texts.RoomStateText).text = "Waiting"; // TODO

        return true;
    }
}
