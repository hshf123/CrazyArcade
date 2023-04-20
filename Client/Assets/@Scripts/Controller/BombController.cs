using Protocol;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using CellPos = Protocol.PCellPos;

public class BombController : MonoBehaviour
{
    Vector3Int[] _upRangeList;
    Vector3Int[] _rightRangeList;
    Vector3Int[] _downRangeList;
    Vector3Int[] _leftRangeList;
    Vector3 correction = new Vector3(0.5f, 0.5f, 0);

    Animator _animator;

    public int SortOrder { get; set; }
    public CellPos CellPos { get; set; }
    public int BombID { get; set; }
    public int Range { get; set; }

    void Start()
    {
        _animator = GetComponent<Animator>();

        _animator.Play("READY");
    }

    public void Init()
    {
        GetComponent<SpriteRenderer>().sortingOrder = SortOrder;
        _upRangeList = new Vector3Int[Range];
        _rightRangeList = new Vector3Int[Range];
        _downRangeList = new Vector3Int[Range];
        _leftRangeList = new Vector3Int[Range];
        for (int i = 0; i < Range; i++)
        {
            _upRangeList[i] = new Vector3Int(CellPos.PosX, CellPos.PosY, 0) + new Vector3Int(0, i + 1, 0);
            _rightRangeList[i] = new Vector3Int(CellPos.PosX, CellPos.PosY, 0) + new Vector3Int(i + 1, 0, 0);
            _downRangeList[i] = new Vector3Int(CellPos.PosX, CellPos.PosY, 0) + new Vector3Int(0, -(i + 1), 0);
            _leftRangeList[i] = new Vector3Int(CellPos.PosX, CellPos.PosY, 0) + new Vector3Int(-(i + 1), 0, 0);
        }
    }

    public void Bomb(Action callback)
    {
        UpWaterCourse();
        RightWaterCourse();
        DownWaterCourse();
        LeftWaterCourse();
        Managers.Resource.Instantiate("WaterCourse", null, (course) =>
        {
            course.transform.position = new Vector3(CellPos.PosX + correction.x, CellPos.PosY + correction.y, 0);
            Managers.Resource.Destroy(course, 0.54f); course.GetComponent<Animator>().Play("CENTER"); course.GetComponent<SpriteRenderer>().sortingOrder = SortOrder;
            Managers.Resource.Destroy(gameObject);
            // Managers.Object.Remove(BombID);
            callback?.Invoke();
        });
    }

    void UpWaterCourse()
    {
        for (int i = 0; i < Range; i++)
        {
            Vector3Int pos = _upRangeList[i];
            if (Managers.Map.CanGo(_upRangeList[i]) == false)
            {
                // Managers.Map.Break(pos);
                break;
            }

            if (i != Range - 1)
                Managers.Resource.Instantiate("WaterCourse", null, (course) => { course.transform.position = pos + correction; course.GetComponent<Animator>().Play("UP"); course.GetComponent<SpriteRenderer>().sortingOrder = SortOrder; Managers.Resource.Destroy(course, 0.54f); });
            else
                Managers.Resource.Instantiate("WaterCourse", null, (course) => { course.transform.position = pos + correction; course.GetComponent<Animator>().Play("UP_END"); course.GetComponent<SpriteRenderer>().sortingOrder = SortOrder; Managers.Resource.Destroy(course, 0.54f); });
        }
    }
    void RightWaterCourse()
    {
        for (int i = 0; i < Range; i++)
        {
            Vector3Int pos = _rightRangeList[i];
            if (Managers.Map.CanGo(pos) == false)
            {
                // Managers.Map.Break(pos);
                break;
            }

            if (i != Range - 1)
                Managers.Resource.Instantiate("WaterCourse", null, (course) => { course.transform.position = pos + correction; course.GetComponent<Animator>().Play("RIGHT"); course.GetComponent<SpriteRenderer>().sortingOrder = SortOrder; Managers.Resource.Destroy(course, 0.54f); });
            else
                Managers.Resource.Instantiate("WaterCourse", null, (course) => { course.transform.position = pos + correction; course.GetComponent<Animator>().Play("RIGHT_END"); course.GetComponent<SpriteRenderer>().sortingOrder = SortOrder; Managers.Resource.Destroy(course, 0.54f); });
        }
    }
    void DownWaterCourse()
    {
        for (int i = 0; i < Range; i++)
        {
            Vector3Int pos = _downRangeList[i];
            if (Managers.Map.CanGo(_downRangeList[i]) == false)
            {
                // Managers.Map.Break(pos);
                break;
            }

            if (i != Range - 1)
                Managers.Resource.Instantiate("WaterCourse", null, (course) => { course.transform.position = pos + correction; course.GetComponent<Animator>().Play("DOWN"); course.GetComponent<SpriteRenderer>().sortingOrder = SortOrder; Managers.Resource.Destroy(course, 0.54f); });
            else
                Managers.Resource.Instantiate("WaterCourse", null, (course) => { course.transform.position = pos + correction; course.GetComponent<Animator>().Play("DOWN_END"); course.GetComponent<SpriteRenderer>().sortingOrder = SortOrder; Managers.Resource.Destroy(course, 0.54f); });
        }
    }
    void LeftWaterCourse()
    {
        for (int i = 0; i < Range; i++)
        {
            Vector3Int pos = _leftRangeList[i];
            if (Managers.Map.CanGo(_leftRangeList[i]) == false)
            {
                // Managers.Map.Break(pos);
                break;
            }

            if (i != Range - 1)
                Managers.Resource.Instantiate("WaterCourse", null, (course) => { course.transform.position = pos + correction; course.GetComponent<Animator>().Play("LEFT"); course.GetComponent<SpriteRenderer>().sortingOrder = SortOrder; Managers.Resource.Destroy(course, 0.54f); });
            else
                Managers.Resource.Instantiate("WaterCourse", null, (course) => { course.transform.position = pos + correction; course.GetComponent<Animator>().Play("LEFT_END"); course.GetComponent<SpriteRenderer>().sortingOrder = SortOrder; Managers.Resource.Destroy(course, 0.54f); });
        }
    }
}
