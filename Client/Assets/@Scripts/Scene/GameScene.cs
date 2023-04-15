using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameScene : BaseScene
{
    Vector3Int[] respawnPos = new Vector3Int[]
    {
        new Vector3Int(-7,5,0),
        new Vector3Int(4,5,0),
        new Vector3Int(-7,-6,0),
        new Vector3Int(4,-6,0),
        new Vector3Int(-5,5,0),
        new Vector3Int(0,5,0),
        new Vector3Int(-5,-6,0),
        new Vector3Int(2,-6,0)
    };


    protected override bool Init()
    {
        if (base.Init() == false)
            return false;

        Managers.UI.ShowSceneUI<UI_GameScene>();
        Managers.Map.LoadMap("ForestMap",
        (map) =>
        {
            Debug.Log(map.name);
            // TEMP
            int idx = 0;
            foreach (var player in Managers.Game.RoomInfo.PlayerList)
            {
                if (player.PlayerId == Managers.Game.PlayerID)
                {
                    Managers.Resource.Instantiate("MyBazzi", null,
                    (myBazzi) =>
                    {
                        MyPlayerController pc = myBazzi.GetComponent<MyPlayerController>();
                        pc.SetStartPos(respawnPos[idx++]);
                    });
                    continue;
                }

                Managers.Resource.Instantiate("Bazzi", null,
                (bazzi) =>
                {
                    PlayerController pc = bazzi.GetComponent<PlayerController>();
                    pc.SetStartPos(respawnPos[idx++]);
                });
            }
        });

        return true;
    }
}
