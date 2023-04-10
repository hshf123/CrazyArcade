using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static Define;

public class BaseScene : MonoBehaviour
{
    public SceneType SceneType = SceneType.Unknown;
    protected bool _init = false;

    public void Awake()
    {
        Init();
    }

    protected virtual bool Init()
    {
        if (_init)
            return false;

        _init = true;
        Managers.Init();

        GameObject go = GameObject.Find("EventSystem");
        if (go == null)
        {
            Managers.Resource.Instantiate("EventSystem", null, (go) =>
            {
                go.name = "@EventSystem";
            });
        }

        return true;
    }

    public virtual void Clear()
    {

    }
}
