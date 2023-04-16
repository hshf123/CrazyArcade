using Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameScene : BaseScene
{
    Vector3 correction = new Vector3(0.5f, 0.5f, 0);

    protected override bool Init()
    {
        if (base.Init() == false)
            return false;

        Managers.UI.ShowSceneUI<UI_GameScene>();
        Managers.Map.LoadMap("ForestMap",
        (map) =>
        {
            Debug.Log(map.name);
            foreach (var player in Managers.Game.Spawn)
            {
                PPlayer playerInfo = player.PlayerInfo;
                PPositionInfo posInfo = player.PosInfo;

                InstantiatePlayer(playerInfo, posInfo);
            }
        });

        return true;
    }

    void InstantiatePlayer(PPlayer playerInfo, PPositionInfo posInfo)
    {
        if (playerInfo.Id == Managers.Game.PlayerID)
        {
            Managers.Resource.Instantiate("MyBazzi", null,
            (myBazzi) =>
            {
                MyPlayerController pc = myBazzi.GetComponent<MyPlayerController>();
                pc.PlayerInfo = playerInfo;
                pc.State = posInfo.State;
                pc.Dir = posInfo.MoveDir;
                pc.WorldPos = new Vector3(posInfo.WorldPos.PosX, posInfo.WorldPos.PosY, 0);
                pc.CellPos = new Vector3Int(posInfo.CellPos.PosX, posInfo.CellPos.PosY, 0);

                Managers.Game.MyPlayer = pc;
                Debug.Log($"MyPlayer : {posInfo.CellPos.PosX}, {posInfo.CellPos.PosY}");
            });
        }
        else
        {
            Managers.Resource.Instantiate("Bazzi", null,
            (bazzi) =>
            {
                PlayerController pc = bazzi.GetComponent<PlayerController>();
                pc.PlayerInfo = playerInfo;
                pc.State = posInfo.State;
                pc.Dir = posInfo.MoveDir;
                pc.WorldPos = new Vector3(posInfo.WorldPos.PosX, posInfo.WorldPos.PosY, 0);
                pc.CellPos = new Vector3Int(posInfo.CellPos.PosX, posInfo.CellPos.PosY, 0);
                Debug.Log($"Player : {posInfo.CellPos.PosX}, {posInfo.CellPos.PosY}");
            });
        }
    }
}
