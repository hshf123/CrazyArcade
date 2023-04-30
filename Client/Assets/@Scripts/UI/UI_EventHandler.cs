using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UIElements;

public class UI_EventHandler : MonoBehaviour, IPointerClickHandler, IPointerDownHandler, IPointerEnterHandler
{
    public event Action OnClickHandler = null;
    public event Action OnPressHandler = null;
    public event Action OnEnterHandler = null;

    public event Action<PointerEventData> OnClickEventHandler = null;

    public void OnPointerClick(PointerEventData eventData)
    {
        OnClickHandler?.Invoke();
        OnClickEventHandler?.Invoke(eventData);
    }

    public void OnPointerDown(PointerEventData eventData)
    {
        OnPressHandler?.Invoke();
    }

    public void OnPointerEnter(PointerEventData eventData)
    {
        OnEnterHandler?.Invoke();
    }
}
