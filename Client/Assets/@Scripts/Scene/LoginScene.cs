using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LoginScene : BaseScene
{
    protected override bool Init()
    {
        if (base.Init() == false)
            return false;

        Debug.Log("Login Scene");
        Managers.Sound.Play(Define.Sound.Bgm, "login_scene");
        Managers.UI.ShowSceneUI<UI_LoginScene>();
        return true;
    }

    public override void Clear()
    {
        Managers.Sound.Clear();
        Managers.UI.Clear();
    }
}
