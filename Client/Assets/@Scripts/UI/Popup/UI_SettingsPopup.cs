using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI_SettingsPopup : UI_Popup
{
    enum GameObjects
    {
        BgmOnImage,
        BgmOffImage,
        EffectOnImage,
        EffectOffImage,
    }

    enum Buttons
    {
        BgmOnOffButton,
        EffectOnOffButton,
        ExitButton,
    }

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Bind<GameObject>(typeof(GameObjects));
        Bind<Button>(typeof(Buttons));
        #region Sound
        Get<Button>((int)Buttons.BgmOnOffButton).gameObject.BindEvent(ButtonEnterSound, Define.UIEvent.Enter);
        Get<Button>((int)Buttons.EffectOnOffButton).gameObject.BindEvent(ButtonEnterSound, Define.UIEvent.Enter);
        Get<Button>((int)Buttons.ExitButton).gameObject.BindEvent(ButtonEnterSound, Define.UIEvent.Enter);
        #endregion
        Get<Button>((int)Buttons.BgmOnOffButton).gameObject.BindEvent(OnClickBgmOnOffButton);
        Get<Button>((int)Buttons.EffectOnOffButton).gameObject.BindEvent(OnClickEffectOnOffButton);
        Get<Button>((int)Buttons.ExitButton).gameObject.BindEvent(OnClickExitButton);

        Managers.Game.SettingPopupOn = true;

        BGMOnOffImage(Managers.Game.BGMOn);
        EffectSoundOnOffImage(Managers.Game.EffectSoundOn);

        return true;
    }

    void ButtonEnterSound()
    {
        Managers.Sound.Play(Define.Sound.Effect, "pt_in_rect");
    }
    void OnClickBgmOnOffButton()
    {
        Managers.Sound.Play(Define.Sound.Effect, "click");
        bool bgmOn = Managers.Game.BGMOn;
        bgmOn = !bgmOn;
        Managers.Game.BGMOn = bgmOn;

        BGMOnOffImage(bgmOn);

        if (!bgmOn)
            Managers.Sound.Stop(Define.Sound.Bgm);
        else
            Managers.Sound.Play(Define.Sound.Bgm);
    }
    void OnClickEffectOnOffButton()
    {
        Managers.Sound.Play(Define.Sound.Effect, "click");
        bool effectSoundOn = Managers.Game.EffectSoundOn;
        effectSoundOn = !effectSoundOn;
        Managers.Game.EffectSoundOn = effectSoundOn;

        EffectSoundOnOffImage(effectSoundOn);

        if (!effectSoundOn)
            Managers.Sound.Stop(Define.Sound.Effect);
        else
            Managers.Sound.Play(Define.Sound.Effect);
    }
    void OnClickExitButton()
    {
        Managers.Sound.Play(Define.Sound.Effect, "click");
        ClosePopupUI();
    }
    void BGMOnOffImage(bool bgmOn)
    {
        Get<GameObject>((int)GameObjects.BgmOnImage).SetActive(bgmOn);
        Get<GameObject>((int)GameObjects.BgmOffImage).SetActive(!bgmOn);
    }
    void EffectSoundOnOffImage(bool effectSoundOn)
    {
        Get<GameObject>((int)GameObjects.EffectOnImage).SetActive(effectSoundOn);
        Get<GameObject>((int)GameObjects.EffectOffImage).SetActive(!effectSoundOn);
    }

    public override void ClosePopupUI()
    {
        Managers.Game.SettingPopupOn = false;
        base.ClosePopupUI();
    }
}
