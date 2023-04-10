using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using Unity.VisualScripting;
using UnityEngine;

public class UIManager
{
    int _order = 20;

    Stack<UI_Popup> _popupStack = new Stack<UI_Popup>();

    public UI_Scene SceneUI { get; set; }

    public GameObject Root
    {
        get
        {
            GameObject root = GameObject.Find("@UI_Root");
            if (root == null)
                root = new GameObject { name = "@UI_Root" };

            return root;
        }
    }

    public void SetCanvas(GameObject go, bool sort = true)
    {
        Canvas canvas = Utils.GetOrAddComponent<Canvas>(go);
        canvas.renderMode = RenderMode.ScreenSpaceOverlay;
        canvas.overrideSorting = true;

        if (sort)
        {
            canvas.sortingOrder = _order;
            _order++;
        }
        else
        {
            canvas.sortingOrder = 0;
        }
    }

    public void MakeSubItem<T>(Transform parent = null, string key = null, Action<T> callback = null) where T : UI_Base
    {
        if (string.IsNullOrEmpty(key))
            key = typeof(T).Name;

        Managers.Resource.Instantiate(key, parent, (go) =>
        {
            T subItem = Utils.GetOrAddComponent<T>(go);
            callback?.Invoke(subItem);
        });
    }

    public void ShowSceneUI<T>(string key = null, Action<T> callback = null) where T : UI_Scene
    {
        if (string.IsNullOrEmpty(key))
            key = typeof(T).Name;

        Managers.Resource.Instantiate(key, Root.transform, (go) =>
        {
            T sceneUI = Utils.GetOrAddComponent<T>(go);
            SceneUI = sceneUI;
            callback?.Invoke(sceneUI);
        });
    }

    public void ShowPopupUI<T>(string key = null, Transform parent = null, Action<T> callback = null) where T : UI_Popup
    {
        if (string.IsNullOrEmpty(key))
            key = typeof(T).Name;

        Managers.Resource.Instantiate(key, null, (go) =>
        {
            T popup = Utils.GetOrAddComponent<T>(go);
            _popupStack.Push(popup);

            if (parent != null)
                go.transform.SetParent(parent);
            else
                go.transform.SetParent(Root.transform);

            callback?.Invoke(popup);
        });
    }

    public T FindPopup<T>() where T : UI_Popup
    {
        return _popupStack.Where(x => x.GetType() == typeof(T)).FirstOrDefault() as T;
    }

    public T PeekPopupUI<T>() where T : UI_Popup
    {
        if (_popupStack.Count == 0)
            return null;

        return _popupStack.Peek() as T;
    }

    public void ClosePopupUI(UI_Popup popup)
    {
        if (_popupStack.Count == 0)
            return;

        if (_popupStack.Peek() != popup)
        {
            Debug.Log("Close Popup Failed!");
            return;
        }

        ClosePopupUI();
    }

    public void ClosePopupUI()
    {
        if (_popupStack.Count == 0)
            return;

        UI_Popup popup = _popupStack.Pop();
        Managers.Resource.Destroy(popup.gameObject);
        popup = null;
        _order--;
    }

    public void CloseAllPopupUI()
    {
        while (_popupStack.Count > 0)
            ClosePopupUI();
    }

    public void Clear()
    {
        CloseAllPopupUI();
        SceneUI = null;
    }
}
