using JetBrains.Annotations;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static Define;
using PositionInfo = Protocol.PPositionInfo;
using MoveDir = Protocol.PMoveDir;
using PlayerState = Protocol.PPlayerState;
using PlayerInfo = Protocol.PPlayer;
using Unity.VisualScripting;
using Protocol;

public class PlayerController : MonoBehaviour
{
    protected Vector3 correction = new Vector3(0.5f, 0.7f, 0);
    #region Component
    protected SpriteRenderer _spriteRenderer;
    protected Animator _animator;
    protected SpriteRenderer _shadow;
    Coroutine _coDead = null;
    protected int _sortOrder;
    #endregion
    #region Protocol
    public PlayerInfo PlayerInfo = new PlayerInfo();
    protected PositionInfo _posInfo = new PositionInfo()
    {
        WorldPos = new PWorldPos(),
        CellPos = new PCellPos()
    };
    protected PositionInfo PosInfo
    {
        get
        {
            return _posInfo;
        }
        set
        {
            if (_posInfo.Equals(value))
                return;

            _posInfo = value;
            UpdateAnimation();
        }
    }
    #endregion

    Vector3 _destPos;
    public Vector3 DestPos
    {
        get
        {
            return _destPos;
        }
        set
        {
            if (_destPos.x == value.x && _destPos.y == value.y)
                return;

            _destPos.x = value.x;
            _destPos.y = value.y;
        }
    }
    public virtual Vector3 WorldPos
    {
        get
        {
            return transform.position;
        }
        set
        {
            if (PosInfo.WorldPos.PosX == value.x && PosInfo.WorldPos.PosY == value.y)
                return;

            _posInfo.WorldPos.PosX = value.x;
            _posInfo.WorldPos.PosY = value.y;
            transform.position = value;
        }
    }
    public virtual Vector3Int CellPos
    {
        get 
        {
            return new Vector3Int(PosInfo.CellPos.PosX, PosInfo.CellPos.PosY, 0); 
        }
        set
        {
            if (PosInfo.CellPos.PosX == value.x && PosInfo.CellPos.PosY == value.y)
                return;

            _posInfo.CellPos.PosX = value.x;
            _posInfo.CellPos.PosY = value.y;
        }
    }
    protected MoveDir _lastDir = MoveDir.Down;
    public virtual MoveDir Dir
    {
        get
        {
            return PosInfo.MoveDir;
        }
        set
        {
            if (PosInfo.MoveDir == value)
                return;

            _posInfo.MoveDir = value;
            if (value != MoveDir.None)
                _lastDir = value;
            UpdateAnimation();
        }
    }
    public virtual PlayerState State
    {
        get { return PosInfo.State; }
        set
        {
            if (PosInfo.State == value)
                return;

            _posInfo.State = value;
            UpdateAnimation();
        }
    }

    void Start()
    {
        Init();
    }
    protected virtual bool Init()
    {
        #region Component
        _spriteRenderer = Utils.GetOrAddComponent<SpriteRenderer>(gameObject);
        _animator = Utils.GetOrAddComponent<Animator>(gameObject);
        _sortOrder = -100;
        _spriteRenderer.sortingOrder = _sortOrder;
        #endregion
        #region Charactor Info

        _shadow = Utils.FindChild<SpriteRenderer>(gameObject, "shadow");
        _shadow.transform.localPosition = new Vector3(0, -0.65f, 0);
        _shadow.sortingOrder = _sortOrder - 1;
        #endregion

        // �ִϸ��̼� ����ȭ��
        UpdateAnimation();
        return true;
    }
    void Update()
    {
        UpdateController();
    }
    protected virtual void UpdateController()
    {
        MovePosition();
        PositionCorrection();
        UpdateSortOrder();
    }
    protected void UpdateAnimation()
    {
        if (_animator == null)
            return;

        switch(State)
        {
            case PlayerState.Idle:
                {
                    if (_lastDir == MoveDir.Up)
                    {
                        _animator.Play("IDLE_UP");
                    }
                    else if (_lastDir == MoveDir.Right)
                    {
                        _animator.Play("IDLE_RIGHT");
                    }
                    else if (_lastDir == MoveDir.Down)
                    {
                        _animator.Play("IDLE_DOWN");
                    }
                    else if (_lastDir == MoveDir.Left)
                    {
                        _animator.Play("IDLE_LEFT");
                    }
                    break;
                }
            case PlayerState.Moving:
                {
                    switch (Dir)
                    {
                        case MoveDir.Up:
                            {
                                _animator.Play("WALK_UP");
                                break;
                            }
                        case MoveDir.Right:
                            {
                                _animator.Play("WALK_RIGHT");
                                break;
                            }
                        case MoveDir.Down:
                            {
                                _animator.Play("WALK_DOWN");
                                break;
                            }
                        case MoveDir.Left:
                            {
                                _animator.Play("WALK_LEFT");
                                break;
                            }
                    }
                    break;
                }
            case PlayerState.Intrap:
                {
                    _animator.Play("TRAP");
                    break;
                }
            case PlayerState.Outtrap:
                {
                    _animator.Play("LIVE");
                    break;
                }
            case PlayerState.Dead:
                {
                    _animator.Play("DIE");
                    break;
                }
            case PlayerState.Win:
                {
                    _animator.Play("WIN");
                    break;
                }
        }
    }
    public void OnDead()
    {
        _coDead = StartCoroutine(CoOnDead());
    }

    protected virtual void MovePosition()
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
                    benchmarkUp += new Vector3(-0.5f, 0.5f, 0);
                    benchmarkDown += new Vector3(0.5f, 0.5f, 0);
                    destPos += (Vector3.up * Time.deltaTime * PlayerInfo.Speed);
                    break;
                }
            case MoveDir.Right:
                {
                    benchmark += new Vector3(0.5f, 0, 0);
                    benchmarkUp += new Vector3(0.5f, -0.5f, 0);
                    benchmarkDown += new Vector3(0.5f, 0.5f, 0);
                    destPos += (Vector3.right * Time.deltaTime * PlayerInfo.Speed);
                    break;
                }
            case MoveDir.Down:
                {
                    benchmark += new Vector3(0, -0.5f, 0);
                    benchmarkUp += new Vector3(-0.5f, -0.5f, 0);
                    benchmarkDown += new Vector3(0.5f, -0.5f, 0);
                    destPos += (Vector3.down * Time.deltaTime * PlayerInfo.Speed);
                    break;
                }
            case MoveDir.Left:
                {
                    benchmark += new Vector3(-0.5f, 0, 0);
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
    protected virtual void PositionCorrection()
    {
        // ���� �̵����̶�� ������ �ʿ䰡 ����.
        if (State == PlayerState.Moving)
            return;

        float dist = (DestPos - WorldPos).magnitude;
        if(dist > Time.deltaTime * PlayerInfo.Speed)
        {
            // �� �����Ӿȿ� ������ �� �ִٸ� ������ �ɷ� ����
            Vector3 dir = (DestPos - WorldPos).normalized;
            WorldPos += (dir * Time.deltaTime * PlayerInfo.Speed);
        }
    }
    protected virtual void UpdateSortOrder()
    {
        _sortOrder = -100 + (Managers.Map.MaxY - CellPos.y) * 2 + 1;
        _spriteRenderer.sortingOrder = _sortOrder;
        _shadow.sortingOrder = _sortOrder - 1;
    }

    IEnumerator CoOnDead()
    {
        yield return new WaitForSeconds(0.45f);

        Managers.Sound.Play(Define.Sound.Effect, "ballon_explosion");
        Managers.Object.RemovePlayer(PlayerInfo.Id);
        Managers.Resource.Destroy(gameObject);
        _coDead = null;
    }
}
