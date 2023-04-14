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

        return true;
    }
}
