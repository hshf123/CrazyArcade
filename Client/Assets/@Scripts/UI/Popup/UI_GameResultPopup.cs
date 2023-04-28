using Google.Protobuf.Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI_GameResultPopup : UI_Popup
{
    enum Images
    {
        WinImage,
        LoseImage_1,
        LoseImage_2,
    }

    GameObject _rank;

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Bind<Image>(typeof(Images));

        Get<Image>((int)Images.WinImage).gameObject.SetActive(false);
        Get<Image>((int)Images.LoseImage_1).gameObject.SetActive(false);
        Get<Image>((int)Images.LoseImage_2).gameObject.SetActive(false);

        _rank = Utils.FindChild(gameObject, "Rank", true);

        return true;
    }

    public void RefreshRankPage(S_GAMEEND pkt)
    {
        foreach (UI_RankSubItem subItem in Utils.FindChilds<UI_RankSubItem>(gameObject, true))
            Managers.Resource.Destroy(subItem.gameObject);

        foreach(var endInfo in pkt.EndInfo)
        {
            InstantiateRankSubItem(endInfo.Rank,endInfo.Player.Level, endInfo.Player.Name, 0, 0, endInfo.Player.Exp, 0);
        }
    }

    void InstantiateRankSubItem(int rank,int level, string name, int kill, int save, float exp, int lucci)
    {
        Managers.UI.MakeSubItem<UI_RankSubItem>(_rank.transform, null,
            (subItem) =>
            {
                subItem.Rank = rank;
                subItem.Level = level;
                subItem.Name = name;
                subItem.Kill = kill;
                subItem.Save = save;
                subItem.Exp = exp;
                subItem.Lucci = lucci;
            });
    }
}
