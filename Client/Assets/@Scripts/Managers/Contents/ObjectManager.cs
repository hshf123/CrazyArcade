using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectManager
{
    public MyPlayerController MyPlayer { get; set; }
    Dictionary<long, PlayerController> _players = new Dictionary<long, PlayerController>();

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
    }

    public PlayerController Find(long id)
    {
        PlayerController pc = null;
        _players.TryGetValue(id, out pc);

        return pc;
    }
}
