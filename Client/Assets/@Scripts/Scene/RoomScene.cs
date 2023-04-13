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

        

        return true;
    }
}
