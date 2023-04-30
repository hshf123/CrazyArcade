using Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChannelScene : BaseScene
{
    UI_ChannelScene _uiChannelScene;

    protected override bool Init()
    {
        if (base.Init() == false)
            return false;

        Managers.Sound.Play(Define.Sound.Bgm, "mode_select_scene");
        Managers.UI.ShowSceneUI<UI_ChannelScene>(null,
            (sceneUI) =>
            {
                _uiChannelScene = sceneUI;
            });

        return true;
    }

    public override void Clear()
    {
        Managers.UI.Clear();
        _uiChannelScene = null;
        Managers.Game.Channels = null;
        Managers.Sound.Clear();
    }
}
