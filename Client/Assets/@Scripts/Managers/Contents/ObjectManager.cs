using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectManager
{
    Dictionary<int, GameObject> _bombs = new Dictionary<int, GameObject>();

    public void Add(int id, GameObject go)
    {
        _bombs.Add(id, go);
    }

    public bool Remove(int id)
    {
        if (_bombs.Remove(id) == false)
            return false;

        return true;
    }

    public void Clear()
    {
        _bombs.Clear();
    }

    public GameObject Find(Vector3Int pos)
    {
        foreach(GameObject go in _bombs.Values)
        {
            BombController bc = go.GetComponent<BombController>();
            if (bc == null)
                Debug.Log("No BombController");

            if (bc.CellPos == pos)
                return bc.gameObject;
        }

        return null;
    }
}
