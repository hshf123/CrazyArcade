using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI_SettingsPopup : UI_Popup
{
    enum Buttons
    {
        SoundOnOffButton,
        ExitButton,
    }

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Bind<Button>(typeof(Buttons));

        return true;
    }

    void OnClickSoundOnOffButton()
    {
        Managers.Sound.Clear();
    }
    void OnClickExitButton()
    {
        ClosePopupUI();
    }
}
