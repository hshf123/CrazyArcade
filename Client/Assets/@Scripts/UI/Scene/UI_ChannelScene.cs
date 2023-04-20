using Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI_ChannelScene : UI_Scene
{
    enum GameObjects
    {
        Content,
    }

    List<UI_ChannelSubItem> _subItems;

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Bind<GameObject>(typeof(GameObjects));

        SubItemsClear();

        _subItems = new List<UI_ChannelSubItem>();

        for (int i = 0; i < Managers.Game.Channels.Count; i++)
        {
            Managers.UI.MakeSubItem<UI_ChannelSubItem>(Get<GameObject>((int)GameObjects.Content).transform, null,
                (subItem) =>
                {
                    subItem.Channel = Managers.Game.Channels[_subItems.Count];
                    _subItems.Add(subItem);
                    subItem.name = $"{subItem.name}_{_subItems.Count}";

                    if (_subItems.Count == Managers.Game.Channels.Count)
                        Managers.Game.Channels = null;
                });
        }

        return true;
    }

    void SubItemsClear()
    {
        UI_ChannelSubItem[] subItems = Utils.FindChilds<UI_ChannelSubItem>(gameObject);
        foreach(UI_ChannelSubItem subItem in subItems)
            Managers.Resource.Destroy(subItem.gameObject);
    }
}
