using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Utils
{
    public static T GetOrAddComponent<T>(GameObject go) where T : UnityEngine.Component
    {
        T component = go.GetComponent<T>();
        if (component == null)
            component = go.AddComponent<T>();
        return component;
    }

    public static T FindChild<T>(GameObject go, string name = null, bool recursive = false) where T : UnityEngine.Object
    {
        if (go == null)
            return null;

        if (recursive == false)
        {
            //Transform transform = go.transform.Find(name);
            //if (transform != null)
            //    return transform.GetComponent<T>();

            for (int i = 0; i < go.transform.childCount; i++)
            {
                Transform transform = go.transform.GetChild(i);
                if (string.IsNullOrEmpty(name) || transform.name == name)
                {
                    T component = transform.GetComponent<T>();
                    if (component != null)
                        return component;
                }
            }
        }
        else
        {
            foreach (T component in go.GetComponentsInChildren<T>())
            {
                if (string.IsNullOrEmpty(name) || component.name == name)
                    return component;
            }
        }

        return null;
    }

    public static GameObject FindChild(GameObject go, string name = null, bool recursive = false)
    {
        Transform transform = FindChild<Transform>(go, name, recursive);
        if (transform != null)
            return transform.gameObject;
        return null;
    }

    public static T[] FindChilds<T>(GameObject go, bool sameObjNameClassName = true) where T : UnityEngine.Component
    {
        T[] childs = go.GetComponentsInChildren<T>();
        if (sameObjNameClassName)
        {
            T[] results = new T[childs.Length];
            int count = 0;
            foreach (T child in childs)
            {
                if (child.name != go.name)
                    results[count++] = child;
            }
            return results;
        }
        else
            return childs;
    }
}
