using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI_GameScene : UI_Scene
{
    enum Buttons
    {
        ExitButton,
    }

    enum Texts
    {
        MapInfoText,
        AnnouncementText,
        TimerText,
    }

    int _gameTime = 180; // 180초
    float _second = 0.0f;

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Managers.UI.MakeSubItem<UI_PingTextSubItem>(transform);
        Managers.UI.MakeSubItem<UI_FPSTextSubItem>(transform);
        Managers.UI.ShowPopupUI<UI_GameStartPopup>();

        Bind<Button>(typeof(Buttons));
        BindText(typeof(Texts));

        _gameTime = 180;
        _second = 0.0f;
        GetText((int)Texts.MapInfoText).text = Managers.Game.MapName;
        GetText((int)Texts.AnnouncementText).text = $"개인전입니다.";
        GetText((int)Texts.TimerText).text = $"{(_gameTime / 60):D2} : {(_gameTime % 60):D2}";

        return true;
    }

    void Update()
    {
        GameTimer();
    }

    void GameTimer()
    {
        _second += Time.deltaTime;
        if (_second >= 1.0f)
        {
            _second = 0;
            _gameTime--;
            GetText((int)Texts.TimerText).text = $"{(_gameTime / 60):D2} : {(_gameTime % 60):D2}";
        }
    }
}
