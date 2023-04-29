using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UI_FPSTextSubItem : UI_Base
{
    enum Texts
    {
        UI_FPSTextSubItem,
    }

    Coroutine _coFPS = null;
    bool _fpsFlag = false;

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        BindText(typeof(Texts));

        transform.localPosition = new Vector3(400.0f, 300.0f, 0);

        return true;
    }

    void Update()
    {
        _coFPS = StartCoroutine(CoFPS());
    }

    IEnumerator CoFPS()
    {
        if (_fpsFlag == true)
            yield break;

        _fpsFlag = true;
        GetText((int)Texts.UI_FPSTextSubItem).text = $"FPS : {(int)(1.0f / Time.deltaTime)}";
        yield return new WaitForSeconds(1f);
        _coFPS = null;
        _fpsFlag = false;
    }
}
