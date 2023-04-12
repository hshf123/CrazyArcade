using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoomScene : BaseScene
{
    protected override bool Init()
    {
        if (base.Init() == false)
            return false;

        Managers.Sound.Clear();

        Managers.UI.ShowSceneUI<UI_RoomScene>(null,
            (sceneUI) =>
            {
                
            });

        return true;
    }
}
