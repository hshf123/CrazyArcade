using Google.Protobuf.Protocol;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;
using System.Runtime.CompilerServices;

public class UI_LoginScene : UI_Scene
{
    TMP_InputField _inputFieldId;
    TMP_InputField _inputFieldPw;

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

    enum Texts
    {
        Input_ID_Text,
    }

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        _inputFieldId = Utils.FindChild<TMP_InputField>(gameObject, "Input_ID", true);
        _inputFieldPw = Utils.FindChild<TMP_InputField>(gameObject, "Input_PW", true);
        Bind<Button>(typeof(Buttons));
        BindText(typeof(Texts));

        Get<Button>((int)Buttons.SignInButton).gameObject.BindEvent(OnClickSignInButton);
        Get<Button>((int)Buttons.LoginButton).gameObject.BindEvent(OnClickLoginButton);
        Get<Button>((int)Buttons.ExitButton).gameObject.BindEvent(OnClickExitButton);

        return true;
    }

    void Update()
    {
        if (_inputFieldId.isFocused && Input.GetKey(KeyCode.Tab))
        {
            _inputFieldPw.Select();
        }
    }

    void OnClickSignInButton()
    {
        // TODO : 회원가입 창 띄우기
    }
    void OnClickLoginButton()
    {
        C_LOGIN loginPkt = new C_LOGIN();
        // LATER 아이디 컨벤션? 비번 해시? 웹서버?

        loginPkt.Id = GetText((int)Texts.Input_ID_Text).text;
        loginPkt.Pw = _inputFieldPw.text;

        Managers.Net.SessionManager.Broadcast(loginPkt);
    }
    void OnClickExitButton()
    {
        Debug.Log("Exit");
        Application.Quit();
    }
}
