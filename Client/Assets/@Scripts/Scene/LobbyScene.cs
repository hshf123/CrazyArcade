using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LobbyScene : BaseScene
{
    protected override bool Init()
    {
        if (base.Init() == false)
            return false;

        Managers.Sound.Clear();

        Managers.UI.ShowSceneUI<UI_LobbyScene>(null,
            (sceneUI) =>
            {

            });

        return true;
    }
}
