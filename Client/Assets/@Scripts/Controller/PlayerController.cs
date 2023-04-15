using JetBrains.Annotations;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static Define;

public class PlayerController : MonoBehaviour
{
    protected Vector3 correction = new Vector3(0.5f, 0.5f, 0);

    protected SpriteRenderer _spriteRenderer;
    protected Animator _animator;
    protected SpriteRenderer _shadow;
    protected Coroutine _coBomb;
    protected bool _bombCool = false;
    protected int _bombId = 1;

    protected int _sortOrder;
    [SerializeField]
    protected float _speed;
    [SerializeField]
    protected int _maxBombCount = 1;
    [SerializeField]
    protected int _bombRange = 1;
    protected int _bombCount = 0;

    protected Vector3Int _cellPos;
    protected MoveDir _lastDir = MoveDir.Down;
    protected MoveDir _moveDir = MoveDir.Down;
    public MoveDir Dir
    {
        get
        {
            return _moveDir;
        }
        set
        {
            if (_moveDir == value)
                return;

            _moveDir = value;
            if (value != MoveDir.None)
                _lastDir = value;
            UpdateAnimation();
        }
    }
    protected PlayerState _state = PlayerState.Idle;
    public PlayerState State
    {
        get { return _state; }
        set
        {
            if (_state == value)
                return;

            _state = value;
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
        _speed = 2f;

        _shadow = Utils.FindChild<SpriteRenderer>(gameObject, "shadow");
        _shadow.transform.localPosition = new Vector3(0, -0.65f, 0);
        _shadow.sortingOrder = _sortOrder - 1;
        #endregion

        return true;
    }
    void Update()
    {
        VirtualUpdate();
    }
    protected virtual void VirtualUpdate()
    {
        MovePosition();
        UpdateSortOrder();
    }

    public void SetStartPos(Vector3Int pos)
    {
        _cellPos = pos;
        Vector3 worldPos = Managers.Map.CurrentGrid.CellToWorld(_cellPos);
        transform.position = worldPos + correction;
    }

    protected void UpdateAnimation()
    {
        switch(_state)
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
                    switch (_moveDir)
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
            case PlayerState.InTrap:
                {
                    _animator.Play("TRAP");
                    break;
                }
            case PlayerState.OutTrap:
                {
                    _animator.Play("LIVE");
                    break;
                }
            case PlayerState.Dead:
                {
                    _animator.Play("DIE");
                    break;
                }
        }
    }
    
    protected void MovePosition()
    {
        if (State != PlayerState.Moving)
            return;

        Vector3 destPos = new Vector3(transform.position.x, transform.position.y, transform.position.z);
        Vector3 benchmark = destPos;
        Vector3 benchmarkUp = destPos;
        Vector3 benchmarkDown = destPos;
        switch (_moveDir)
        {
            case MoveDir.Up:
                {
                    Vector3 dir = (Vector3.up * Time.deltaTime * _speed);
                    benchmark += dir + new Vector3(0, 0.5f, 0);
                    benchmarkUp += dir + new Vector3(-0.5f, 0.5f, 0);
                    benchmarkDown += dir + new Vector3(0.5f, 0.5f, 0);
                    destPos += dir;
                    break;
                }
            case MoveDir.Right:
                {
                    Vector3 dir = (Vector3.right * Time.deltaTime * _speed);
                    benchmark += dir + new Vector3(0.5f, 0, 0);
                    benchmarkUp += dir + new Vector3(0.5f, -0.5f, 0);
                    benchmarkDown += dir + new Vector3(0.5f, 0.5f, 0);
                    destPos += dir;
                    break;
                }
            case MoveDir.Down:
                {
                    Vector3 dir = (Vector3.down * Time.deltaTime * _speed);
                    benchmark += dir + new Vector3(0, -0.5f, 0);
                    benchmarkUp += dir + new Vector3(-0.5f, -0.5f, 0);
                    benchmarkDown += dir + new Vector3(0.5f, -0.5f, 0);
                    destPos += dir;
                    break;
                }
            case MoveDir.Left:
                {
                    Vector3 dir = (Vector3.left * Time.deltaTime * _speed);
                    benchmark += dir + new Vector3(-0.5f, 0, 0);
                    benchmarkUp += dir + new Vector3(-0.5f, 0.5f, 0);
                    benchmarkDown += dir + new Vector3(-0.5f, -0.5f, 0);
                    destPos += dir;
                    break;
                }
        }
        if (_moveDir != MoveDir.None)
        {
            Vector3Int destCellPos = Managers.Map.CurrentGrid.WorldToCell(benchmark);
            bool isBomb = Managers.Object.Find(destCellPos) == null;
            if ((Managers.Map.CanGo(destCellPos) && isBomb) || (isBomb == false && destCellPos == _cellPos))
            {
                Vector3 dist = destPos - transform.position;
                float xrange = Mathf.Abs(destPos.x) - Mathf.Floor(Mathf.Abs(destPos.x));
                float yrange = Mathf.Abs(destPos.y) - Mathf.Floor(Mathf.Abs(destPos.y));
                if (dist.y != 0 && (xrange <= 0.51f && xrange >= 0.49f))
                {
                    // 추가 기준점 2개가 필요하지 않은 경우, y축 이동
                    transform.position = destPos;
                }
                else if (dist.x != 0 && (yrange <= 0.51f && yrange >= 0.49f))
                {
                    // 추가 기준점 2개가 필요하지 않은 경우, x축 이동
                    transform.position = destPos;
                }
                else
                {
                    Vector3Int destCellPosUp = Managers.Map.CurrentGrid.WorldToCell(benchmarkUp);
                    Vector3Int destCellPosDown = Managers.Map.CurrentGrid.WorldToCell(benchmarkDown);
                    bool upCanGo = Managers.Map.CanGo(destCellPosUp) || ((destCellPos == _cellPos) && (Managers.Object.Find(destCellPos) != null));
                    bool downCanGo = Managers.Map.CanGo(destCellPosDown) || ((destCellPos == _cellPos) && (Managers.Object.Find(destCellPos) != null));
                    if (upCanGo && downCanGo)
                    {
                        transform.position = destPos;
                    }
                    else if (upCanGo == false)
                    {
                        transform.position += (benchmark - benchmarkUp).normalized * Time.deltaTime * _speed;
                    }
                    else if (downCanGo == false)
                    {
                        transform.position += (benchmark - benchmarkDown).normalized * Time.deltaTime * _speed;
                    }
                }
                _cellPos = Managers.Map.CurrentGrid.WorldToCell(transform.position);
            }
        }
        //Debug.Log($"Move To {_cellPos}");
    }
    protected virtual void UpdateSortOrder()
    {
        _sortOrder = -100 + (Managers.Map.MaxY - _cellPos.y) * 2 + 1;
        _spriteRenderer.sortingOrder = _sortOrder;
        _shadow.sortingOrder = _sortOrder - 1;
    }
    protected IEnumerator Bomb()
    {
        Vector3Int pos = Managers.Map.CurrentGrid.WorldToCell(transform.position + new Vector3(0, -0.3f, 0));
        if (_bombCool == false && Managers.Object.Find(pos) == null
            && _bombCount < _maxBombCount)
        {
            _bombCool = true;
             _bombCount++;      
            Managers.Resource.Instantiate("Bomb", null,
                (bomb) =>
                {
                    Managers.Object.Add(_bombId, bomb);
                    BombController bc = bomb.GetComponent<BombController>();
                    bc.CellPos = pos;
                    bomb.transform.position = pos + correction;
                    bc.BombID = _bombId;
                    bc.Range = _bombRange;
                    bc.SortOrder = _sortOrder;
                    _bombId++;
                    bc.Init();
                    bc.Bomb(() => { _bombCount--; });
                });

            yield return new WaitForSeconds(0.25f);
            _coBomb = null;
            _bombCool = false;
        }
    }
}
