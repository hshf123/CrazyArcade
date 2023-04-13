using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UI_ChatBoxSubItem : UI_Base
{
    enum Texts
    {
        ChatBoxSubItemText,
    }

    string _msg = "LeafC : æ»≥Á«œººø‰";

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        BindText(typeof(Texts));
        GetText((int)Texts.ChatBoxSubItemText).text = _msg;
        return true;
    }

    public void SetChat(string msg)
    {
        _msg = msg;
    }
}
