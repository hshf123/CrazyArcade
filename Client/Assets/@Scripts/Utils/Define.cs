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

    public enum UIEvent
    {
        Click,
        Press
    }

    public enum SceneType
    {
        Unknown,
        DevScene,
        LoginScene,
        ChannelScene,
        LobbyScene,
        RoomScene,
        GameScene,
    }

    public enum Sound
    {
        Bgm,
        Effect,
        Max
    }
}
