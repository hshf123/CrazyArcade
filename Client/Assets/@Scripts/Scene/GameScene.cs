using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameScene : BaseScene
{
    protected override bool Init()
    {
        if (base.Init() == false)
            return false;

        Managers.UI.ShowSceneUI<UI_GameScene>();
        Managers.Map.LoadMap("ForestMap",
        (map) =>
        {
            Debug.Log(map.name);
            Managers.Resource.Instantiate("Bazzi",null,
                (bazzi)=>
                {
                });
        });

        return true;
    }
}
