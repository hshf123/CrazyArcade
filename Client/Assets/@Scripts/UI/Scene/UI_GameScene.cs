using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI_GameScene : UI_Scene
{
    enum Buttons
    {
        ExitButton,
    }

    enum Texts
    {
        MapInfoText,
        AnnouncementText,
        TimerText,
    }

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Managers.UI.MakeSubItem<UI_PingTextSubItem>(transform);
        Managers.UI.MakeSubItem<UI_FPSTextSubItem>(transform);
        Managers.UI.ShowPopupUI<UI_GameStartPopup>();

        Bind<Button>(typeof(Buttons));
        BindText(typeof(Texts));

        GetText((int)Texts.MapInfoText).text = Managers.Game.MapName;

        return true;
    }
}
