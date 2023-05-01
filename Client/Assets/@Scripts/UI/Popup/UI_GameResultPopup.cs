using Google.Protobuf.Collections;
using Google.Protobuf.Protocol;
using Protocol;
using System;
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

    SortedDictionary<int, UI_RankSubItem> _subItems = new SortedDictionary<int, UI_RankSubItem>();
    GameObject _rank;
    public RepeatedField<PRoomEnd> EndInfo;

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Bind<Image>(typeof(Images));

        Get<Image>((int)Images.WinImage).gameObject.SetActive(false);
        Get<Image>((int)Images.LoseImage_1).gameObject.SetActive(false);
        Get<Image>((int)Images.LoseImage_2).gameObject.SetActive(false);

        _rank = Utils.FindChild(gameObject, "Rank", true);
        RefreshRankPage();
        Managers.Sound.Clear();

        return true;
    }

    void RefreshRankPage()
    {
        foreach (UI_RankSubItem subItem in Utils.FindChilds<UI_RankSubItem>(gameObject, true))
            Managers.Resource.Destroy(subItem.gameObject);

        foreach (var endInfo in EndInfo)
        {
            InstantiateRankSubItem(endInfo.Rank, endInfo.PlayerInfo.Level, endInfo.PlayerInfo.Name, 0, 0, endInfo.PlayerInfo.Exp, 0);
            if(endInfo.Rank == 1 && endInfo.PlayerInfo.Id == Managers.Game.PlayerID)
            {
                // 1등인 경우
                Get<Image>((int)Images.WinImage).gameObject.SetActive(true);
                Managers.Object.MyPlayer.State = endInfo.PlayerPosInfo.State;
                Managers.Sound.Play(Define.Sound.Effect, "win");
            }
            else if(endInfo.PlayerInfo.Id == Managers.Game.PlayerID)
            {
                // 그 외인 경우
                Get<Image>((int)Images.LoseImage_1).gameObject.SetActive(true);
                Get<Image>((int)Images.LoseImage_2).gameObject.SetActive(true);
                Managers.Object.MyPlayer.State = endInfo.PlayerPosInfo.State;
                Managers.Sound.Play(Define.Sound.Effect, "defeat");
            }
        }
    }
    void InstantiateRankSubItem(int rank, int level, string name, int kill, int save, float exp, int lucci)
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
                        subItem.transform.SetSiblingIndex(rank - 1);
                    });
    }
}
