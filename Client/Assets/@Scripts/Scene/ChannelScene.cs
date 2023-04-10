using Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChannelScene : BaseScene
{
    UI_ChannelScene _uiChannelScene;

    protected override bool Init()
    {
        if (base.Init() == false)
            return false;

        //ChannelInfo = new ChannelInfo();
        //ChannelInfo.ChannelCount = 5;
        //for (int i = 0; i < 5; i++)
        //{
        //    Channel channel = new Channel();
        //    channel.ChannelId = i + 1;
        //    channel.CurrentPlayerCount = 0;
        //    channel.MaxPlayerCount = 500;
        //
        //    ChannelInfo.Channels.Add(channel);
        //}

        Managers.UI.ShowSceneUI<UI_ChannelScene>(null,
            (sceneUI) =>
            {
                _uiChannelScene = sceneUI;
            });

        return true;
    }
}
