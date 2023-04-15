using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UI_RoomSubItem : UI_Base
{
    public int RoomID { get; set; }
    public string RoomName { get; set; }
    public int CurrentPlayerCount { get; set; }
    public int MaxPlayerCount { get; set; }
    public string RoomState { get; set; } = "Waiting";

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

        GetText((int)Texts.RoomNameText).text = RoomName;
        GetText((int)Texts.RoomNumberText).text = $"{RoomID:D2}";
        GetText((int)Texts.RoomPlayerCountText).text = $"{CurrentPlayerCount}/{MaxPlayerCount}";
        GetText((int)Texts.RoomStateText).text = RoomState; // TODO

        return true;
    }
}
