using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static Define;
using PositionInfo = Protocol.PPositionInfo;
using MoveDir = Protocol.PMoveDir;
using PlayerState = Protocol.PPlayerState;
using Google.Protobuf.Protocol;
using UnityEngine.Experimental.AI;
using Unity.VisualScripting;

public class MyPlayerController : PlayerController
{
    protected SpriteRenderer _cursor;
    #region Bomb
    protected Coroutine _coBomb;
    protected bool _bombCool = false;
    #endregion
    bool _updateFlag = false;

    public override Vector3 WorldPos
    {
        get => base.WorldPos;
        set
        {
            Vector3 prevValue = base.WorldPos;
            base.WorldPos = value;
            if (base.WorldPos == prevValue)
                return;
        }
    }
    public override Vector3Int CellPos
    {
        get => base.CellPos;
        set
        {
            Vector3Int prevValue = base.CellPos;
            base.CellPos = value;
            if (base.CellPos == prevValue)
                return;
            _updateFlag = true;
        }
    }
    public override MoveDir Dir
    {
        get => PosInfo.MoveDir;
        set
        {
            MoveDir prevValue = _lastDir;
            base.Dir = value;
            if (_lastDir == prevValue)
                return;
            _updateFlag = true;
        }
    }
    public override PlayerState State
    {
        get => PosInfo.State;
        set
        {
            PlayerState prevValue = base.State;
            base.State = value;
            if (base.State == prevValue)
                return;
            _updateFlag = true;

            Debug.Log($"Change State : {prevValue} -> {value}");
        }
    }

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
        CheckUpdateFlag();
    }

    void InputDir()
    {
        if (State == PlayerState.Dead)
            return;

        if(State == PlayerState.Intrap)
        {
            TrapInputDir();
            return;
        }

        if (Input.GetKey(KeyCode.UpArrow))
        {
            Dir = MoveDir.Up;
            State = PlayerState.Moving;
        }
        else if (Input.GetKey(KeyCode.RightArrow))
        {
            Dir = MoveDir.Right;
            State = PlayerState.Moving;
        }
        else if (Input.GetKey(KeyCode.DownArrow))
        {
            Dir = MoveDir.Down;
            State = PlayerState.Moving;
        }
        else if (Input.GetKey(KeyCode.LeftArrow))
        {
            Dir = MoveDir.Left;
            State = PlayerState.Moving;
        }
        else
        {
            Dir = MoveDir.None;
            State = PlayerState.Idle;
        }

        if (Input.GetKey(KeyCode.Space))
        {
            _coBomb = StartCoroutine(Bomb());
            // Bomb();
        }
    }
    void TrapInputDir()
    {
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
        }
    }
    protected override void UpdateSortOrder()
    {
        base.UpdateSortOrder();
        _cursor.sortingOrder = _sortOrder + 1;
    }
    void CheckUpdateFlag()
    {
        if (_updateFlag)
        {
            C_MOVE movePkt = new C_MOVE();
            movePkt.PositionInfo = PosInfo;
            Managers.Net.SessionManager.Broadcast(movePkt);
            _updateFlag = false;
        }
    }
    IEnumerator Bomb()
    {
        if (_bombCool)
            yield break;

        _bombCool = true;
        C_BOMB bombPkt = new C_BOMB();
        bombPkt.PosInfo = PosInfo;
        Managers.Net.SessionManager.Broadcast(bombPkt);
        yield return new WaitForSeconds(0.25f);
        _coBomb = null;
        _bombCool = false;
    }
}
