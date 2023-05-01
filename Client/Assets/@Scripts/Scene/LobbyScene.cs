using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LobbyScene : BaseScene
{
    protected override bool Init()
    {
        if (base.Init() == false)
            return false;

        Managers.Sound.Play(Define.Sound.Bgm, "mode_select_scene");
        Managers.UI.ShowSceneUI<UI_LobbyScene>();

        return true;
    }

    public override void Clear()
    {
        Managers.UI.Clear();
        Managers.Game.Rooms = null;
        Managers.Game.LobbyUI = null;
        Managers.Sound.Clear();
    }
}
