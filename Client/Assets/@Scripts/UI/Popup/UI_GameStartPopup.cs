using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UI_GameStartPopup : UI_Popup
{
    Coroutine _coGameStart = null;

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        _coGameStart = StartCoroutine(CoGameStart());

        return true;
    }

    IEnumerator CoGameStart()
    {
        yield return new WaitForSeconds(1.5f);

        ClosePopupUI();
        _coGameStart = null;
    }
}
