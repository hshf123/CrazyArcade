using Google.Protobuf.Collections;
using Protocol;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Playables;

[Serializable]
public class GameData
{
    public bool BGMOn = true;
    public bool EffectSoundOn = true;
}

public class GameManagerEx
{
    public RepeatedField<PChannel> Channels { get; set; } = new RepeatedField<PChannel>();
    public RepeatedField<PRoom> Rooms { get; set; } = new RepeatedField<PRoom>();

    public long PlayerID { get; set; }
    public int ChannelID { get; set; }

    public UI_LobbyScene LobbyUI { get; set; }
    public UI_RoomScene RoomUI { get; set; }
    public PRoom Room { get; set; }
    public bool IsLeader { get { return Room.LeaderId == PlayerID; } }

    GameData _gameData = new GameData();
    public GameData SaveData { get { return _gameData; } set { _gameData = value; } }

    public string MapInfo { get; set; } = "TestMap";

    #region Option
    public bool BGMOn
    {
        get { return _gameData.BGMOn; }
        set { _gameData.BGMOn = value; }
    }

    public bool EffectSoundOn
    {
        get { return _gameData.EffectSoundOn; }
        set { _gameData.EffectSoundOn = value; }
    }
    #endregion

    public void Init()
    {
        if (LoadGame())
            return;

        SaveGame();
    }

    #region Save&Load
    string _path;

    public void SaveGame()
    {
        
    }

    public bool LoadGame()
    {

        return true;
    }
    #endregion
}
