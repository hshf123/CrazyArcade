using Protocol;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static UnityEngine.Tilemaps.TilemapRenderer;
using ItemType = Protocol.PItemType;

public class GameScene : BaseScene
{
    Vector3 correction = new Vector3(0.5f, 0.7f, 0);

    protected override bool Init()
    {
        if (base.Init() == false)
            return false;

        Managers.Sound.Play(Define.Sound.Effect, "game_start");
        Managers.Sound.Play(Define.Sound.Bgm, "play_scene");
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

                Managers.Object.MyPlayer = pc;
                Managers.Object.AddPlayer(pc.PlayerInfo.Id, pc);
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
                Managers.Object.AddPlayer(pc.PlayerInfo.Id, pc);
                Debug.Log($"Player : {posInfo.CellPos.PosX}, {posInfo.CellPos.PosY}");
            });
        }
    }
    public void InstantiateBomb(PPlayer playerInfo, PCellPos cellPos, long ownerId)
    {
        Managers.Resource.Instantiate("Bomb", null,
            (bomb) =>
            {
                BombController bc = bomb.GetComponent<BombController>();
                bc.CellPos = cellPos;
                bc.Range = playerInfo.BombRange;
                bc.SortOrder = -100 + (Managers.Map.MaxY - cellPos.PosY) * 2;
                bc.OwnerId = ownerId;
                Managers.Object.AddBomb(new Vector3Int(cellPos.PosX, cellPos.PosY, 0), bomb.GetComponent<BombController>());
                bomb.transform.position = new Vector3(bc.CellPos.PosX + correction.x, bc.CellPos.PosY + correction.y - 0.2f, 0);
                bc.Init();
                Managers.Sound.Play(Define.Sound.Effect, "bomb_set");
            });
    }
    public void InstantiateItem(Vector3Int pos, ItemType itemType)
    {
        Managers.Resource.Instantiate("Item", null, (item) => 
        {
            ItemController ic = item.GetComponent<ItemController>();
            ic.ItemType = itemType;
            item.transform.position = pos + new Vector3(0.5f, 0.5f, 0);
            Managers.Object.AddItem(pos, ic);
            Managers.Sound.Play(Define.Sound.Effect, "ItemGen");
        });
    }

    public override void Clear()
    {
        Managers.UI.Clear();
        Managers.Map.DestroyMap();
        Managers.Object.Clear();
        Managers.Game.MapName = null;
        Managers.Sound.Clear();
    }
}
