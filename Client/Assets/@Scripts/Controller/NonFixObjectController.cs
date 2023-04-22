using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NonFixObjectController : MonoBehaviour
{
    Animator _animator;

    [SerializeField]
    public int PosX;
    [SerializeField]
    public int PosY;

    public Vector3Int CellPos { get; set; }
    string _name;

    void Start()
    {
        _animator = GetComponent<Animator>();
        CellPos = new Vector3Int(PosX, PosY, 0);
        _name = gameObject.name;
        if(_name == "Grass")
        {
            _animator.Play("GRASS");
        }
        else if(_name == "Flower")
        {
            _animator.Play("FLOWER");
        }
    }

    public void OnDestroy()
    {
        if(_animator == null)
            return;

        if (_name == "Grass")
        {
            _animator.Play("GRASS_DESTROY");
        }
        else if (_name == "Flower")
        {
            _animator.Play("FLOWER_DESTROY");
        }
        Managers.Resource.Destroy(gameObject, 0.4f);
    }
}
