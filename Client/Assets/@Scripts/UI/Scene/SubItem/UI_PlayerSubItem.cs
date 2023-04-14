using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UI_PlayerSubItem : UI_Base
{
    string _name;
    string _level;

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

        GetText((int)Texts.PlayerName).text = _name;
        GetText((int)Texts.PlayerLevel).text = _level;

        return true;
    }

    public void SetPlayerName(string name)
    {
        _name = $"{name}";
    }

    public void SetPlayerLevel(int level)
    {
        _level = $"Lv. {level:D2}";
    }
}
