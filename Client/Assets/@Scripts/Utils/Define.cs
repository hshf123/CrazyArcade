using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Define
{
    public enum ObjectType
    {
        Fix = 1,
        NonFix = 2,
    }

    public enum PlayerState
    {
        Idle,
        Moving,
        InTrap,
        OutTrap,
        Dead,
    }

    public enum MoveDir
    {
        None,
        Up,
        Right,
        Down,
        Left,
    }

    public enum UIEvent
    {
        Click,
        Press
    }

    public enum SceneType
    {
        Unknown,
        LoginScene,
        ChannelScene,
        LobbyScene,
        GameScene,
    }

    public enum Sound
    {
        Bgm,
        Effect,
        Max
    }
}
