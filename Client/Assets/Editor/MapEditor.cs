using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;
using System.IO;
using static UnityEngine.Rendering.VirtualTexturing.Debugging;
using System;
using UnityEngine.AddressableAssets;
using System.Xml.Linq;

#if UNITY_EDITOR
using UnityEditor;
#endif

public class MapEditor
{
#if UNITY_EDITOR

    [MenuItem("Tools/CreateForestMap %^m")]
    private static void CreateForestMap()
    {
        GameObject go = Resources.Load<GameObject>("Prefabs/Map/ForestMap");

        GameObject prefabMap = new GameObject() { name = go.name };
        prefabMap.AddComponent<Grid>();

        Tilemap tileBase = Utils.FindChild<Tilemap>(go, "Tilemap_Base", true);
        Tilemap fixObject = Utils.FindChild<Tilemap>(go, "Tilemap_FixObject", true);
        Tilemap nonFixObject1 = Utils.FindChild<Tilemap>(go, "Tilemap_NonFixObject_1", true);
        Tilemap nonFixObject2 = Utils.FindChild<Tilemap>(go, "Tilemap_NonFixObject_2", true);
        Tilemap range = Utils.FindChild<Tilemap>(go, "Tilemap_Range", true);

        GameObject tileBaseCpy = UnityEngine.Object.Instantiate(tileBase.gameObject);
        tileBaseCpy.transform.parent = prefabMap.transform;
        tileBaseCpy.name = tileBase.name;
        tileBaseCpy.transform.localPosition = tileBase.transform.localPosition;
        tileBaseCpy.transform.localScale = tileBase.transform.localScale;

        using (var writer = File.CreateText($"Assets/@Resources/MapInfo/ForestMapInfo.txt"))
        {
            const int Fix = 1;
            const int NonFix = 2;

            writer.WriteLine(range.cellBounds.xMin);
            writer.WriteLine(range.cellBounds.xMax);
            writer.WriteLine(range.cellBounds.yMin);
            writer.WriteLine(range.cellBounds.yMax);

            int mapY = range.cellBounds.yMax - range.cellBounds.yMin + 1;
            int mapX = range.cellBounds.xMax - range.cellBounds.xMin + 1;
            int[,] mapInfo = new int[mapY, mapX];

            // 바위(고정)
            {
                GameObject folder = new GameObject("FixObject");
                folder.transform.parent = prefabMap.transform;
                folder.transform.localPosition = new Vector2(0, 0);
                folder.transform.localScale = new Vector2(1, 1);
                int sortorder = -100;
                for (int y = range.cellBounds.yMax; y >= range.cellBounds.yMin; y--)
                {
                    for (int x = range.cellBounds.xMin; x <= range.cellBounds.xMax; x++)
                    {
                        TileBase tb = fixObject.GetTile(new Vector3Int(x, y, 0));
                        if (tb != null)
                        {
                            GameObject obj = new GameObject() { name = "Rock" };
                            obj.transform.parent = folder.transform;
                            obj.AddComponent<SpriteRenderer>();
                            obj.GetComponent<SpriteRenderer>().sprite = AssetDatabase.LoadAssetAtPath("Assets/@Resources/Sprites/map/Fixobject/object_3.png", typeof(Sprite)) as Sprite;
                            obj.GetComponent<SpriteRenderer>().sortingOrder = sortorder;
                            obj.transform.localPosition = new Vector2(x + 0.5f, y + 0.5f);
                            obj.transform.localScale = new Vector2(1, 1);

                            mapInfo[y - range.cellBounds.yMin, x - range.cellBounds.xMin] = Fix;
                        }
                    }
                    sortorder+=2;
                }
            }
            // 부서지는 오브젝트들
            {
                // 풀
                GameObject folder = new GameObject("NonFixObject");
                folder.transform.parent = prefabMap.transform;
                folder.transform.localPosition = new Vector2(0, 0);
                folder.transform.localScale = new Vector2(1, 1);
                {
                    int sortorder = -100;
                    for (int y = range.cellBounds.yMax; y >= range.cellBounds.yMin; y--)
                    {
                        for (int x = range.cellBounds.xMin; x <= range.cellBounds.xMax; x++)
                        {
                            TileBase tb = nonFixObject1.GetTile(new Vector3Int(x, y, 0));
                            if (tb != null)
                            {
                                GameObject obj = new GameObject() { name = "Grass" };
                                obj.transform.parent = folder.transform;
                                SpriteRenderer sr = obj.AddComponent<SpriteRenderer>();
                                Animator animator = obj.AddComponent<Animator>();
                                animator.runtimeAnimatorController = AssetDatabase.LoadAssetAtPath("Assets/@Resources/Animation/Object/NonFixObjectAnimController.controller", typeof(RuntimeAnimatorController)) as RuntimeAnimatorController;
                                sr.sprite = AssetDatabase.LoadAssetAtPath("Assets/@Resources/Sprites/map/NonFixobject/block_6.png", typeof(Sprite)) as Sprite;
                                sr.sortingOrder = sortorder;
                                NonFixObjectController nfobj = obj.AddComponent<NonFixObjectController>();
                                nfobj.PosX = x;
                                nfobj.PosY = y; obj.transform.localPosition = new Vector2(x + 0.5f, y + 0.5f);
                                obj.transform.localScale = new Vector2(1, 1);
                                mapInfo[y - range.cellBounds.yMin, x - range.cellBounds.xMin] = NonFix;
                            }
                        }
                        sortorder+=2;
                    }
                }
                // 꽃
                {
                    int sortorder = -100;
                    for (int y = range.cellBounds.yMax; y >= range.cellBounds.yMin; y--)
                    {
                        for (int x = range.cellBounds.xMin; x <= range.cellBounds.xMax; x++)
                        {
                            TileBase tb = nonFixObject2.GetTile(new Vector3Int(x, y, 0));
                            if (tb != null)
                            {
                                GameObject obj = new GameObject() { name = "Flower" };
                                obj.transform.parent = folder.transform;
                                SpriteRenderer sr = obj.AddComponent<SpriteRenderer>();
                                Animator animator = obj.AddComponent<Animator>();
                                animator.runtimeAnimatorController = AssetDatabase.LoadAssetAtPath("Assets/@Resources/Animation/Object/NonFixObjectAnimController.controller", typeof(RuntimeAnimatorController)) as RuntimeAnimatorController;
                                sr.sprite = AssetDatabase.LoadAssetAtPath("Assets/@Resources/Sprites/map/NonFixobject/block_4.png", typeof(Sprite)) as Sprite;
                                sr.sortingOrder = sortorder;
                                NonFixObjectController nfobj = obj.AddComponent<NonFixObjectController>();
                                nfobj.PosX = x;
                                nfobj.PosY = y;
                                obj.transform.localPosition = new Vector2(x + 0.5f, y + 0.5f);
                                obj.transform.localScale = new Vector2(1, 1);
                                mapInfo[y - range.cellBounds.yMin, x - range.cellBounds.xMin] = NonFix;
                            }
                        }
                        sortorder+=2;
                    }
                }
            }
            // 범위(고정, invisible)
            {
                GameObject folder = new GameObject("Range");
                folder.transform.parent = prefabMap.transform;
                folder.transform.localPosition = new Vector2(0, 0);
                folder.transform.localScale = new Vector2(1, 1);
                for (int y = range.cellBounds.yMax; y >= range.cellBounds.yMin; y--)
                {
                    for (int x = range.cellBounds.xMin; x <= range.cellBounds.xMax; x++)
                    {
                        TileBase tb = range.GetTile(new Vector3Int(x, y, 0));
                        if (tb != null)
                        {
                            GameObject obj = new GameObject() { name = "AbsoluteWall" };
                            obj.transform.parent = folder.transform;
                            obj.AddComponent<SpriteRenderer>();
                            obj.GetComponent<SpriteRenderer>().sprite = AssetDatabase.LoadAssetAtPath("Assets/@Resources/Sprites/map/Fixobject/object_3.png", typeof(Sprite)) as Sprite;
                            obj.transform.localPosition = new Vector2(x + 0.5f, y + 0.5f);
                            obj.transform.localScale = new Vector2(1, 1);
                            mapInfo[y - range.cellBounds.yMin, x - range.cellBounds.xMin] = Fix;
                        }
                    }
                }
                folder.SetActive(false);
            }

            for (int y = mapY - 1; y >= 0; y--)
            {
                for (int x = 0; x < mapX; x++)
                {
                    writer.Write(mapInfo[y, x]);
                }
                writer.WriteLine();
            }
        }
        StreamReader reader = new StreamReader(Application.dataPath + "/@Resources/MapInfo/ForestMapInfo.txt");
        using (var writer = File.CreateText($"../Common/MapData/ForestMapInfo.txt"))
        {
            while (!reader.EndOfStream)
            {
                string line = reader.ReadLine();
                writer.WriteLine(line);
            }

        }
        reader.Close();
        PrefabUtility.SaveAsPrefabAsset(prefabMap, $"Assets/@Resources/Prefabs/Map/{go.name}.prefab");

        return;
    }

#endif
}