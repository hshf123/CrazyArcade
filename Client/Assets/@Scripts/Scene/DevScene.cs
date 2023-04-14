using Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DevScene : BaseScene
{
    protected override bool Init()
    {
        if (base.Init() == false)
            return false;

        // Managers.Scene.ChangeScene<ChannelScene>(Define.SceneType.ChannelScene);
        Screen.SetResolution(800, 600, false);

        return true;
    }
}
