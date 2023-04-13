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
    public ChannelInfo ChannelInfo { get; set; }
    public LobbyInfo LobbyInfo { get; set; }
    public long PlayerID { get; set; }
    public int ChannelID { get; set; }
    public int RoomID { get; set; }

    public UI_LobbyScene Lobby { get; set; }

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
