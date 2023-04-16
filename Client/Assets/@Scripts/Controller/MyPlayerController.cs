using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static Define;
using PositionInfo = Protocol.PPositionInfo;
using MoveDir = Protocol.PMoveDir;
using PlayerState = Protocol.PPlayerState;
using Google.Protobuf.Protocol;
using UnityEngine.Experimental.AI;

public class MyPlayerController : PlayerController
{
    protected SpriteRenderer _cursor;
    #region Bomb
    protected Coroutine _coBomb;
    protected bool _bombCool = false;
    protected int _bombId = 1;
    [SerializeField]
    protected float _speed;
    [SerializeField]
    protected int _maxBombCount = 1;
    [SerializeField]
    protected int _bombRange = 1;
    protected int _bombCount = 0;
    #endregion

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
    protected override void MovePosition()
    {
        PlayerState prevState = State;
        Vector3Int prevCellPos = CellPos;

        InputDir();
        base.MovePosition();

        if(prevState != State || prevCellPos != CellPos)
        {
            C_MOVE movePkt = new C_MOVE();
            movePkt.PositionInfo = PosInfo;
            Managers.Net.SessionManager.Broadcast(movePkt);
        }
    }
    protected override void UpdateSortOrder()
    {
        base.UpdateSortOrder();
        _cursor.sortingOrder = _sortOrder + 1;
    }


    protected IEnumerator Bomb()
    {
        // Vector3Int pos = Managers.Map.CurrentGrid.WorldToCell(transform.position + new Vector3(0, -0.3f, 0));
        // if (_bombCool == false && Managers.Object.Find(pos) == null
        //     && _bombCount < _maxBombCount)
        // {
        //     _bombCool = true;
        //     _bombCount++;
        //     Managers.Resource.Instantiate("Bomb", null,
        //         (bomb) =>
        //         {
        //             Managers.Object.Add(_bombId, bomb);
        //             BombController bc = bomb.GetComponent<BombController>();
        //             bc.CellPos = pos;
        //             bomb.transform.position = pos + correction;
        //             bc.BombID = _bombId;
        //             bc.Range = _bombRange;
        //             bc.SortOrder = _sortOrder;
        //             _bombId++;
        //             bc.Init();
        //             bc.Bomb(() => { _bombCount--; });
        //         });
        // 
        //     yield return new WaitForSeconds(0.25f);
        //     _coBomb = null;
        //     _bombCool = false;
        // }

        yield return new WaitForFixedUpdate();
    }
}
