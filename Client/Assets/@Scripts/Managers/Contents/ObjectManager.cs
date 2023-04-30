using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectManager
{
    public MyPlayerController MyPlayer { get; set; }
    Dictionary<long, PlayerController> _players = new Dictionary<long, PlayerController>();
    Dictionary<Vector3Int, BombController> _bombs = new Dictionary<Vector3Int, BombController>();
    Dictionary<Vector3Int, ItemController> _items = new Dictionary<Vector3Int, ItemController>();

    public void AddPlayer(long id, PlayerController pc)
    {
        _players.Add(id, pc);
    }
    public void AddBomb(Vector3Int pos, BombController bc)
    {
        _bombs.Add(pos, bc);
    }
    public void AddItem(Vector3Int pos, ItemController ic)
    {
        _items.Add(pos, ic);
    }

    public bool RemovePlayer(long id)
    {
        if (_players.Remove(id) == false)
            return false;

        return true;
    }
    public bool RemoveBomb(Vector3Int pos)
    {
        if (_bombs.Remove(pos) == false)
            return false;

        return true;
    }
    public bool RemoveItem(Vector3Int pos)
    {
        if (_items.Remove(pos) == false)
            return false;

        return true;
    }

    public PlayerController FindPlayer(long id)
    {
        PlayerController pc = null;
        _players.TryGetValue(id, out pc);

        return pc;
    }
    public BombController FindBomb(Vector3Int pos)
    {
        BombController bc = null;
        _bombs.TryGetValue(pos, out bc);

        return bc;
    }
    public ItemController FindItem(Vector3Int pos)
    {
        ItemController ic = null;
        _items.TryGetValue(pos, out ic);

        return ic;
    }

    public void Clear()
    {
        MyPlayer = null;
        _players.Clear();
        _bombs.Clear();
        _items.Clear();
    }
}
