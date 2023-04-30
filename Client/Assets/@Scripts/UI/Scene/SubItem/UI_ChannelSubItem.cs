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

    public PChannel Channel { get; set; }

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Bind<Button>(typeof(Buttons));
        #region Sound
        Get<Button>((int)Buttons.EnterButton).gameObject.BindEvent(ButtonEnterSound, Define.UIEvent.Enter);
        #endregion
        Get<Button>((int)Buttons.EnterButton).gameObject.BindEvent(OnClickEnterButton);

        _populationBar.SetPopulationBar(Channel.CurrentPlayerCount, Channel.MaxPlayerCount);

        return true;
    }

    void ButtonEnterSound()
    {
        Managers.Sound.Play(Define.Sound.Effect, "pt_in_rect");
    }
    void OnClickEnterButton()
    {
        Debug.Log($"{Channel.ChannelId}번 채널 선택");
        Managers.Sound.Play(Define.Sound.Effect, "click");
        C_CHANNELCHOICE channelChoicePkt = new C_CHANNELCHOICE();
        channelChoicePkt.ChannelId = Channel.ChannelId;
        Managers.Net.SessionManager.Broadcast(channelChoicePkt);
    }
}
