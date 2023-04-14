using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UI_PlayerSubItem : UI_Base
{
    enum Texts
    {
        PlayerName,
        PlayerLevel,
    }

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        BindText(typeof(Texts));

        return true;
    }

    public void SetPlayerName(string name)
    {
        GetText((int)Texts.PlayerName).text = $"{name}";
    }

    public void SetPlayerName(int level)
    {
        GetText((int)Texts.PlayerLevel).text = $"Lv. {level:D2}";
    }
}
