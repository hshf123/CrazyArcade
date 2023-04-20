using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectManager
{
    public MyPlayerController MyPlayer { get; set; }
    Dictionary<long, PlayerController> _players = new Dictionary<long, PlayerController>();
    Dictionary<Vector3Int, BombController> _bombs = new Dictionary<Vector3Int, BombController>();

    public void Add(long id, PlayerController pc)
    {
        _players.Add(id, pc);
    }

    public bool Remove(long id)
    {
        if (_players.Remove(id) == false)
            return false;

        return true;
    }

    public void Clear()
    {
        _players.Clear();
        _bombs.Clear();
    }

    public PlayerController Find(long id)
    {
        PlayerController pc = null;
        _players.TryGetValue(id, out pc);

        return pc;
    }

    public void SetBomb(Vector3Int pos, BombController bc)
    {
        _bombs.Add(pos, bc);
    }

    public bool BombEnd(Vector3Int pos)
    {
        if (_bombs.Remove(pos) == false)
            return false;

        return true;
    }

    public BombController FindBomb(Vector3Int pos)
    {
        BombController bc = null;
        _bombs.TryGetValue(pos, out bc);

        return bc;
    }
}
