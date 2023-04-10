using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class Extension
{
    public static T GetOrAddComponent<T>(this GameObject go) where T : UnityEngine.Component
    {
        return Utils.GetOrAddComponent<T>(go);
    }

    public static GameObject FindChild(this GameObject gameObject, string name = null, bool recursive = false)
    {
        Transform transform = Utils.FindChild<Transform>(gameObject, name, recursive);
        if (transform == null)
            return null;

        return transform.gameObject;
    }

    public static void BindEvent(this GameObject go, Action action, Define.UIEvent type = Define.UIEvent.Click)
    {
        UI_Base.BindEvent(go, action, type);
    }
}
