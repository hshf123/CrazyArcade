using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Diagnostics;
using UnityEngine.SceneManagement;

public class Managers : MonoBehaviour
{
    Managers() { }
    static Managers _instance = null;
    public static Managers Instance { get { return _instance; } }

    MapManager _map = new MapManager();
    ObjectManager _object = new ObjectManager();

    GameManagerEx _game = new GameManagerEx();
    NetworkManager _net = new NetworkManager();
    ResourceManager _resource = new ResourceManager();
    SceneManagerEx _scene = new SceneManagerEx();
    SoundManager _sound = new SoundManager();
    UIManager _ui = new UIManager();

    public static MapManager Map { get { return _instance?._map; } }
    public static ObjectManager Object { get { return _instance?._object; } }

    public static GameManagerEx Game { get { return Instance?._game; } }
    public static NetworkManager Net { get { return Instance?._net; } }
    public static ResourceManager Resource { get { return Instance?._resource; } }
    public static SceneManagerEx Scene { get { return Instance?._scene; } }
    public static SoundManager Sound { get { return Instance?._sound; } }
    public static UIManager UI { get { return Instance?._ui; } }

    public static void Init()
    {
        if (_instance == null)
        {
            GameObject go = GameObject.Find("@Managers");
            if (go == null)
                go = new GameObject { name = "@Managers" };

            _instance = Utils.GetOrAddComponent<Managers>(go);
            DontDestroyOnLoad(go);

            _instance._game.Init();
            _instance._net.Init();
            _instance._sound.Init();
        }
    }
}
