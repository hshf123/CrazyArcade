using Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI_ChannelScene : UI_Scene
{
    enum GameObjects
    {
        ChannelItem,
    }

    List<UI_ChannelSubItem> _subItems;

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Bind<GameObject>(typeof(GameObjects));

        SubItemsClear();

        _subItems = new List<UI_ChannelSubItem>();

        for (int i = 0; i < Managers.Game.ChannelInfo.ChannelCount; i++)
        {
            Managers.UI.MakeSubItem<UI_ChannelSubItem>(Get<GameObject>((int)GameObjects.ChannelItem).transform, null,
                (subItem) =>
                {
                    subItem.Channel = Managers.Game.ChannelInfo.Channels[_subItems.Count];
                    _subItems.Add(subItem);
                    subItem.name = $"{subItem.name}_{_subItems.Count}";

                    if (_subItems.Count == Managers.Game.ChannelInfo.ChannelCount)
                        Managers.Game.ChannelInfo = null;
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
