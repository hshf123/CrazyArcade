using Google.Protobuf.Collections;
using Protocol;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UI;

public class UI_RoomScene : UI_Scene
{
    // 채팅 패킷은 오면 바로 띄우면 되고, 내가 들어오기전에 대화했던 내용은 표시할 필요가 없다...
    // 방은 6개 단위로 표현

    enum Buttons
    {
        MakeRoomButton,
        RightButton,
        LeftButton,
        ChatSendButton,
    }

    RepeatedField<Room> _rooms = new RepeatedField<Room>();
    int _roomPage = 0;
    GameObject _roomList;

    public override bool Init()
    {
        if (base.Init() == false)
            return false;

        Bind<Button>(typeof(Buttons));

        RoomInfo roominfo = Managers.Game.RoomInfo;
        _rooms = roominfo.Rooms;
        _roomList = gameObject.FindChild("RoomList", true);

        Get<Button>((int)Buttons.ChatSendButton).gameObject.BindEvent(OnClickChatSendButton);
        Get<Button>((int)Buttons.RightButton).gameObject.BindEvent(OnClickRightButton);
        Get<Button>((int)Buttons.LeftButton).gameObject.BindEvent(OnClickLeftButton);

        RefreshRoomPage();

        return true;
    }

    void RefreshRoomPage()
    {
        ClearRoomPage();

        for (int i = _roomPage * 6; i < (_roomPage + 1) * 6; i++)
        {
            if (i >= _rooms.Count)
            {
                Managers.UI.MakeSubItem<UI_RoomDummySubItem>(_roomList.transform);
            }
            else
            {
                Managers.UI.MakeSubItem<UI_RoomSubItem>(_roomList.transform);
            }
        }
    }
    void ClearRoomPage()
    {
        UI_Base[] childs = Utils.FindChilds<UI_Base>(_roomList, false);
        foreach (UI_Base child in childs)
        {
            Managers.Resource.Destroy(child.gameObject);
        }
    }

    void OnClickMakeRoomButton()
    {
        
    }

    void OnClickChatSendButton()
    {
        // TODO : 채팅 패킷
    }

    void OnClickRightButton()
    {
        int maxPageCount = _rooms.Count / 6;
        _roomPage = Mathf.Min(_roomPage + 1, maxPageCount);
    }

    void OnClickLeftButton()
    {
        _roomPage = Mathf.Max(_roomPage - 1, 0);
    }
}
