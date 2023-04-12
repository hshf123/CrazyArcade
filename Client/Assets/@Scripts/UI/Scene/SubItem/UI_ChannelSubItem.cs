using Google.Protobuf.Protocol;
using Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI_ChannelSubItem : UI_Base
{
    [SerializeField]
    PopulationBar _populationBar;

    enum Buttons
    {
        EnterButton
    }

    public Channel Channel { get; set; }

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Bind<Button>(typeof(Buttons));

        Get<Button>((int)Buttons.EnterButton).gameObject.BindEvent(OnClickEnterButton);

        _populationBar.SetPopulationBar(Channel.CurrentPlayerCount, Channel.MaxPlayerCount);

        return true;
    }

    void OnClickEnterButton()
    {
        Debug.Log($"{Channel.ChannelId}�� ä�� ����");
        C_CHANNELCHOIC channelChoicePkt = new C_CHANNELCHOIC();
        channelChoicePkt.ChannelId = Channel.ChannelId;
        channelChoicePkt.PlayerId = Managers.Game.PlayerID;
        Managers.Net.SessionManager.Broadcast(channelChoicePkt);
    }
}
