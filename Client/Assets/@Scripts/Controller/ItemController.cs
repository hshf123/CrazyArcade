using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using ItemType = Protocol.PItemType;

public class ItemController : MonoBehaviour
{
    Animator _animator;
    ItemType _type;

    void Start()
    {
        _animator = GetComponent<Animator>();

        switch (_type)
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

    public void SetItemType(ItemType type)
    {
        _type = type;
    }
}
