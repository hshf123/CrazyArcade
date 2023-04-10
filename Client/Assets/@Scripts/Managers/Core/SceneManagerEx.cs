using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AddressableAssets;
using UnityEngine.ResourceManagement.AsyncOperations;
using UnityEngine.ResourceManagement.ResourceProviders;
using UnityEngine.SceneManagement;

public class SceneManagerEx
{
    private Define.SceneType _curSceneType = Define.SceneType.Unknown;

    public Define.SceneType CurrentSceneType
    {
        get
        {
            if (_curSceneType != Define.SceneType.Unknown)
                return _curSceneType;
            return CurrentScene.SceneType;
        }
        set { _curSceneType = value; }
    }

    public BaseScene CurrentScene { get { return GameObject.FindObjectOfType<BaseScene>(); } }

    public void ChangeScene<T>(Define.SceneType type) where T : UnityEngine.Object
    {
        Debug.Log(CurrentScene);
        CurrentScene.Clear();

        _curSceneType = type;
        SceneManager.LoadScene(GetSceneName(type));
    }

    string GetSceneName(Define.SceneType type)
    {
        string name = System.Enum.GetName(typeof(Define.SceneType), type);
        return name;
    }

    //string GetSceneName(Define.SceneType type)
    //{
    //    string name = System.Enum.GetName(typeof(Define.SceneType), type);
    //    char[] letters = name.ToLower().ToCharArray();
    //    letters[0] = char.ToUpper(letters[0]);
    //    return new string(letters);
    //}
}
