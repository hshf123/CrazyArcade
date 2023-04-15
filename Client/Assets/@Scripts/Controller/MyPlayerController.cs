using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static Define;

public class MyPlayerController : PlayerController
{
    protected SpriteRenderer _cursor;

    protected override bool Init()
    {
        if (base.Init() == false)
            return false;

        _cursor = Utils.FindChild<SpriteRenderer>(gameObject, "cursor");
        _cursor.transform.localPosition = new Vector3(0, 0.5f, 0);
        _cursor.sortingOrder = _sortOrder + 1;

        return true;
    }
    protected override void VirtualUpdate()
    {
        InputDir();
        base.VirtualUpdate();
    }

    void InputDir()
    {
        State = PlayerState.Moving;
        if (Input.GetKey(KeyCode.UpArrow))
        {
            Dir = MoveDir.Up;
        }
        else if (Input.GetKey(KeyCode.RightArrow))
        {
            Dir = MoveDir.Right;
        }
        else if (Input.GetKey(KeyCode.DownArrow))
        {
            Dir = MoveDir.Down;
        }
        else if (Input.GetKey(KeyCode.LeftArrow))
        {
            Dir = MoveDir.Left;
        }
        else
        {
            Dir = MoveDir.None;
            State = PlayerState.Idle;
        }

        if (Input.GetKey(KeyCode.Space))
        {
            _coBomb = StartCoroutine(Bomb());
        }
    }
    protected override void UpdateSortOrder()
    {
        base.UpdateSortOrder();
        _cursor.sortingOrder = _sortOrder + 1;
    }
}
