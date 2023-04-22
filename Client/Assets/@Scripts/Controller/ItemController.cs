using Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using ItemType = Protocol.PItemType;

public class ItemController : MonoBehaviour
{
    Animator _animator;
    SpriteRenderer _spriteRenderer;
    public ItemType ItemType { get; set; }

    void Start()
    {
        _animator = GetComponent<Animator>();
        _spriteRenderer = GetComponent<SpriteRenderer>();
        _spriteRenderer.sortingOrder = -100 + (Managers.Map.MaxY - (int)Mathf.Floor(transform.position.y)) * 2 + 1;
        switch (ItemType)
        {
            case ItemType.Incspeed:
                _animator.Play("IncSpeed");
                break;
            case ItemType.Incbombrange:
                _animator.Play("IncBombRange");
                break;
            case ItemType.Incbombcount:
                _animator.Play("IncBombCount");
                break;
            case ItemType.Maxbombrange:
                _animator.Play("MaxBombRange");
                break;
        }
    }
}
