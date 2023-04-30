using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using Unity.VisualScripting;
using UnityEngine;
using static Define;

public class MapManager
{
    public Grid CurrentGrid { get; private set; }

    public int MinX { get; set; }
    public int MaxX { get; set; }
    public int MinY { get; set; }
    public int MaxY { get; set; }

    Dictionary<Vector3Int, NonFixObjectController> _nonFixObjects = new Dictionary<Vector3Int, NonFixObjectController>();
    int[,] _blocks;

    public bool CanGo(Vector3Int pos)
    {
        if (pos.x < MinX || pos.x > MaxX)
            return false;
        if (pos.y < MinY || pos.y > MaxY)
            return false;

        int x = pos.x - MinX;
        int y = MaxY - pos.y;
        if (_blocks[y, x] != 0)
            return false;

        return true;
    }

    public void Break(Vector3Int pos)
    {
        if (pos.x < MinX || pos.x > MaxX)
            return;
        if (pos.y < MinY || pos.y > MaxY)
            return;

        int x = pos.x - MinX;
        int y = MaxY - pos.y;
        if (_blocks[y, x] != (int)BlockType.NonFix)
            return;

        _blocks[y, x] = 0;
        NonFixObjectController nfobj;
        if (_nonFixObjects.TryGetValue(pos, out nfobj) == false)
        {
            Debug.Log($"Break Fail {pos} No Object");
            return;
        }
        _nonFixObjects.Remove(pos);
        nfobj.OnDestroy();
    }

    public void LoadMap(string mapName, Action<GameObject> callback = null)
    {
        DestroyMap();

        Managers.Resource.Instantiate(mapName, null,
            (map) =>
            {
                CurrentGrid = map.GetComponent<Grid>();
                callback?.Invoke(map);
                // NonFixObject 따로 저장
                NonFixObjectController[] nonFixes = Utils.FindChilds<NonFixObjectController>(Utils.FindChild(map, "NonFixObject"), false);
                foreach (NonFixObjectController nfobj in nonFixes)
                {
                    _nonFixObjects.Add(CurrentGrid.WorldToCell(nfobj.transform.position), nfobj);
                }
            }
            );

        Managers.Resource.LoadAsync<TextAsset>("ForestMapInfo",
            (txt) =>
            {
                StringReader reader = new StringReader(txt.text);

                MinX = int.Parse(reader.ReadLine());
                MaxX = int.Parse(reader.ReadLine());
                MinY = int.Parse(reader.ReadLine());
                MaxY = int.Parse(reader.ReadLine());

                int xCount = MaxX - MinX + 1;
                int yCount = MaxY - MinY + 1;
                _blocks = new int[yCount, xCount];

                for (int y = 0; y < yCount; y++)
                {
                    string line = reader.ReadLine();
                    for (int x = 0; x < xCount; x++)
                    {
                        _blocks[y, x] = line[x] - '0';
                    }
                }
            });
    }

    public void DestroyMap()
    {
        GameObject map = GameObject.Find("ForestMap");
        if (map != null)
        {
            GameObject.Destroy(map);
            CurrentGrid = null;
        }
        _nonFixObjects.Clear();
        _blocks = null;
    }
}
