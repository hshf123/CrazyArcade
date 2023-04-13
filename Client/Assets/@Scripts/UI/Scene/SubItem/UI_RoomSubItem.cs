using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UI_RoomSubItem : UI_Base
{
    GameObject _roomList;

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

        _roomList = gameObject.FindChild("RoomList");

        return true;
    }
}
