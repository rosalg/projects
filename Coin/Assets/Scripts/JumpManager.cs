using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class JumpManager : MonoBehaviour, IPointerDownHandler, IPointerUpHandler
{
    bool _pressed = false;

    public void OnPointerDown(PointerEventData eventData)
    {
       _pressed = true;
    }

    public void OnPointerUp(PointerEventData eventData)
    {
        _pressed = false;
    }

    void Update()
    {
        if (!_pressed)
            return;

        GameObject.Find("PlayerB").GetComponent<PlayerMovement>().Jump();
        GameObject.Find("PlayerW").GetComponent<PlayerMovement>().Jump();
        AudioManager.instance.Play("JumpSound");
    }
}
