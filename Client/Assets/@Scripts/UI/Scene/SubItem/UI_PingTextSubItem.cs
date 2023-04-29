using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UI_PingTextSubItem : UI_Base
{
    enum Texts
    {
        UI_PingTextSubItem,
    }

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        BindText(typeof(Texts));

        transform.localPosition = new Vector3(360.0f, 300.0f, 0);

        return true;
    }

    void Update()
    {
        GetText((int)Texts.UI_PingTextSubItem).text = $"{Managers.Game.Ping}ms";
    }
}
