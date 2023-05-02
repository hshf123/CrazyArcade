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
using Protocol;

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

            CellPos = Managers.Map.CurrentGrid.WorldToCell(WorldPos);
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
            MoveDir prevDir = _lastDir;
            base.Dir = value;
            if (prevDir == _lastDir)
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
        }
    }
    Vector3Int _frontCellPos;

    protected override bool Init()
    {
        if (base.Init() == false)
            return false;

        _cursor = Utils.FindChild<SpriteRenderer>(gameObject, "cursor");
        _cursor.transform.localPosition = new Vector3(0, 0.5f, 0);
        _cursor.sortingOrder = _sortOrder + 1;

        _frontCellPos = CellPos;

        return true;
    }
    protected override void UpdateController()
    {
        InputDir();
        base.UpdateController();
        CheckUpdateFlag();
    }

    void InputDir()
    {
        if (State == PlayerState.Dead || State == PlayerState.Win)
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
    protected override void MovePosition()
    {
        if (State != PlayerState.Moving && State != PlayerState.Intrap)
            return;

        // ���� ��ġ ����
        Vector3 destPos = WorldPos;
        Vector3 benchmark = destPos;
        Vector3 benchmarkUp = destPos;
        Vector3 benchmarkDown = destPos;
        switch (Dir)
        {
            // �̵� ���⿡ ���� �浹 ������ ��ǥ�� ���� �̵� ��ġ ����
            case MoveDir.Up:
                {
                    benchmark += new Vector3(0, 0.5f, 0);
                    _frontCellPos = Managers.Map.CurrentGrid.WorldToCell(CellPos + new Vector3(0, 0.5f, 0));
                    benchmarkUp += new Vector3(-0.5f, 0.5f, 0);
                    benchmarkDown += new Vector3(0.5f, 0.5f, 0);
                    destPos += (Vector3.up * Time.deltaTime * PlayerInfo.Speed);
                    break;
                }
            case MoveDir.Right:
                {
                    benchmark += new Vector3(0.5f, 0, 0);
                    _frontCellPos = Managers.Map.CurrentGrid.WorldToCell(CellPos + new Vector3(0.5f, 0, 0));
                    benchmarkUp += new Vector3(0.5f, -0.5f, 0);
                    benchmarkDown += new Vector3(0.5f, 0.5f, 0);
                    destPos += (Vector3.right * Time.deltaTime * PlayerInfo.Speed);
                    break;
                }
            case MoveDir.Down:
                {
                    benchmark += new Vector3(0, -0.5f, 0);
                    _frontCellPos = Managers.Map.CurrentGrid.WorldToCell(CellPos + new Vector3(0, -0.5f, 0));
                    benchmarkUp += new Vector3(-0.5f, -0.5f, 0);
                    benchmarkDown += new Vector3(0.5f, -0.5f, 0);
                    destPos += (Vector3.down * Time.deltaTime * PlayerInfo.Speed);
                    break;
                }
            case MoveDir.Left:
                {
                    benchmark += new Vector3(-0.5f, 0, 0);
                    _frontCellPos = Managers.Map.CurrentGrid.WorldToCell(CellPos + new Vector3(-0.5f, 0, 0));
                    benchmarkUp += new Vector3(-0.5f, 0.5f, 0);
                    benchmarkDown += new Vector3(-0.5f, -0.5f, 0);
                    destPos += (Vector3.left * Time.deltaTime * PlayerInfo.Speed);
                    break;
                }
        }
        if (Dir != MoveDir.None)
        {
            // �̵� ������ ������
            Vector3Int destCellPos = Managers.Map.CurrentGrid.WorldToCell(benchmark);
            bool isBomb = Managers.Object.FindBomb(destCellPos) == null; // �ش� ���⿡ ��ǳ���� �ִ��� üũ
            if ((Managers.Map.CanGo(destCellPos) && isBomb) || (isBomb == false && destCellPos == CellPos))
            {
                // �� �� �ְ� ��ǳ���� ���� ��� or ��ǳ���� ������ ��ǳ���̶� ���� ĭ�� ��� (���� ���ڸ����� ��ǳ���� ������ ���)
                Vector3 dist = destPos - WorldPos; // ��ǥ ��ġ������ �Ÿ�
                float xrange = Mathf.Abs(destPos.x) - Mathf.Floor(Mathf.Abs(destPos.x));
                float yrange = Mathf.Abs(destPos.y) - Mathf.Floor(Mathf.Abs(destPos.y));
                if (dist.y != 0 && (xrange <= (0.5f + Time.deltaTime * PlayerInfo.Speed) && xrange >= (0.5f - Time.deltaTime * PlayerInfo.Speed)))
                {
                    // y�� �̵� (���η� �̵�)
                    WorldPos = destPos;
                }
                else if (dist.x != 0 && (yrange <= (0.5f + Time.deltaTime * PlayerInfo.Speed) && yrange >= (0.5f - Time.deltaTime * PlayerInfo.Speed)))
                {
                    // x�� �̵� (���η� �̵�)
                    WorldPos = destPos;
                }
                else
                {
                    // �浹�� ���� ��� or ���� ��¦ ���ļ� �̵� ������ �ʿ��� ��� (��¦ �о ����� ����)
                    Vector3Int destCellPosUp = Managers.Map.CurrentGrid.WorldToCell(benchmarkUp);
                    Vector3Int destCellPosDown = Managers.Map.CurrentGrid.WorldToCell(benchmarkDown);
                    bool upCanGo = Managers.Map.CanGo(destCellPosUp) || ((destCellPos == CellPos) && (Managers.Object.FindBomb(destCellPos) != null));
                    bool downCanGo = Managers.Map.CanGo(destCellPosDown) || ((destCellPos == CellPos) && (Managers.Object.FindBomb(destCellPos) != null));
                    if (upCanGo && downCanGo)
                    {
                        // �� �Ʒ� �� �� �ո� ��� (�浹�� ���� ���)
                        WorldPos = destPos;
                    }
                    else if (upCanGo == false)
                    {
                        // ������ �ݴ�� �̵� (������ ��������� �Ʒ��� ��¦ �̵�)
                        WorldPos += (benchmark - benchmarkUp).normalized * Time.deltaTime * PlayerInfo.Speed;
                    }
                    else if (downCanGo == false)
                    {
                        // ������ �ݴ�� �̵� (�Ʒ����� ��������� ���� ��¦ �̵�)
                        WorldPos += (benchmark - benchmarkDown).normalized * Time.deltaTime * PlayerInfo.Speed;
                    }
                }
                CellPos = Managers.Map.CurrentGrid.WorldToCell(WorldPos);
            }
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
            movePkt.FrontPos = new PCellPos();
            movePkt.FrontPos.PosX = _frontCellPos.x;
            movePkt.FrontPos.PosY = _frontCellPos.y;
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
        bombPkt.CellPos = PosInfo.CellPos;
        Managers.Net.SessionManager.Broadcast(bombPkt);
        yield return new WaitForSeconds(0.2f);
        _coBomb = null;
        _bombCool = false;
    }
}
