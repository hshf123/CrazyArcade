using Google.Protobuf.Protocol;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;
using System.Runtime.CompilerServices;

public class UI_LoginScene : UI_Scene
{
    enum Buttons
    {
        DreamServerButton,
        HappyServerButton,
        _1pButton,
        _2pButton,
        SignInButton,
        LoginButton,
        ExitButton,
    }

    enum InputFields
    {
        Input_ID,
        Input_PW,
    }

    enum Texts
    {
        Input_ID_Text,
    }

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Bind<Button>(typeof(Buttons));
        BindText(typeof(Texts));
        BindInputField(typeof(InputFields));
        #region Sound
        Get<Button>((int)Buttons.SignInButton).gameObject.BindEvent(ButtonEnterSound, Define.UIEvent.Enter);
        Get<Button>((int)Buttons.LoginButton).gameObject.BindEvent(ButtonEnterSound, Define.UIEvent.Enter);
        Get<Button>((int)Buttons.ExitButton).gameObject.BindEvent(ButtonEnterSound, Define.UIEvent.Enter);
        #endregion
        Get<Button>((int)Buttons.SignInButton).gameObject.BindEvent(OnClickSignInButton);
        Get<Button>((int)Buttons.LoginButton).gameObject.BindEvent(OnClickLoginButton);
        Get<Button>((int)Buttons.ExitButton).gameObject.BindEvent(OnClickExitButton);

        return true;
    }

    void Update()
    {
        if (GetInputField((int)InputFields.Input_ID).isFocused && Input.GetKey(KeyCode.Tab))
        {
            GetInputField((int)InputFields.Input_PW).Select();
        }

        if (GetInputField((int)InputFields.Input_PW).isFocused && Input.GetKey(KeyCode.Return))
        {
            OnClickLoginButton();
        }
    }

    void ButtonEnterSound()
    {
        Managers.Sound.Play(Define.Sound.Effect, "pt_in_rect");
    }
    void OnClickSignInButton()
    {
        // TODO : 회원가입 창 띄우기
        Managers.Sound.Play(Define.Sound.Effect, "click");
    }
    void OnClickLoginButton()
    {
        Managers.Sound.Play(Define.Sound.Effect, "click");
        C_LOGIN loginPkt = new C_LOGIN();
        // LATER 아이디 컨벤션? 비번 해시? 웹서버?

        loginPkt.Id = GetText((int)Texts.Input_ID_Text).text;
        loginPkt.Pw = GetInputField((int)InputFields.Input_PW).text;

        Managers.Net.SessionManager.Broadcast(loginPkt);
    }
    void OnClickExitButton()
    {
        Managers.Sound.Play(Define.Sound.Effect, "click");
        Debug.Log("Exit");
        Application.Quit();
    }
}
