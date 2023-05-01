using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LobbyScene : BaseScene
{
    protected override bool Init()
    {
        if (base.Init() == false)
            return false;

        if (Managers.Sound.GetBGMName() != "lobby_scene")
            Managers.Sound.Play(Define.Sound.Bgm, "lobby_scene");
        Managers.UI.ShowSceneUI<UI_LobbyScene>(null,
            (sceneUI) =>
            {

            });

        return true;
    }

    public override void Clear()
    {
        Managers.UI.Clear();
        Managers.Game.Rooms = null;
        Managers.Game.LobbyUI = null;
    }
}
