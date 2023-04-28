using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI_RankSubItem : UI_Base
{
    public int Rank { get; set; }
    public int Level { get; set; }
    public string Name { get; set; }
    public int Kill { get; set; }
    public int Save { get; set; }
    public float Exp { get; set; }
    public int Lucci { get; set; }

    enum Texts
    {
        RankText,
        LevelText,
        IDText,
        KillText,
        SaveText,
        ExpText,
        LucciText,
    }

    enum Images
    {
        WinMiniImage,
        LoseMiniImage,
    }

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        BindText(typeof(Texts));
        Bind<Image>(typeof(Images));

        if(Rank != 1)
            Get<Image>((int)Images.WinMiniImage).gameObject.SetActive(false);
        else
            Get<Image>((int)Images.LoseMiniImage).gameObject.SetActive(false);

        GetText((int)Texts.RankText).text = $"{Rank}";
        GetText((int)Texts.LevelText).text = $"Lv. {Level:D2}";
        GetText((int)Texts.IDText).text = $"{Name}";
        GetText((int)Texts.KillText).text = $"{Kill}";
        GetText((int)Texts.SaveText).text = $"{Save}";
        GetText((int)Texts.ExpText).text = $"+{Exp}";
        GetText((int)Texts.LucciText).text = $"+{Lucci}";

        return true;
    }
}
