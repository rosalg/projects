using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    public CharacterController2D controller;
    public float runSpeed = 40f;
    public Animator animator;
    public Joystick joystick;

    private float horizontalMove = 0f;
    public bool isJumping = false;
    private GameManager gameManager;

    IEnumerator Start()
    {
        yield return new WaitForSeconds(0.5f);
        joystick = FindObjectOfType<Joystick>();
        gameManager = FindObjectOfType<GameManager>();
    }

    void Update()
    {
        if (gameManager == null)
        {
            return;
        }
        if (gameManager.isLoading)
        {
            horizontalMove = 0;
            animator.SetFloat("Speed", 0f);
            return;
        }

        if (joystick.Horizontal >= .5f)
        {
            horizontalMove = runSpeed;
        }
        else if (joystick.Horizontal < .5f && joystick.Horizontal > 0.2f)
        {
            horizontalMove = runSpeed / 2;
        }
        else if(joystick.Horizontal < -0.2f && joystick.Horizontal >= -0.5f)
        {
            horizontalMove = -runSpeed / 2;
        }
        else if (joystick.Horizontal <= -0.5f)
        {
            horizontalMove = -runSpeed;
        }
        else
        {
            horizontalMove = 0;
        }

        animator.SetFloat("Speed", Mathf.Abs(horizontalMove));
    }
    
    public void OnLanding()
    {
        animator.SetBool("IsJumping", false);
    }


    void FixedUpdate()
    {
        controller.Move(horizontalMove * Time.fixedDeltaTime, isJumping);
        isJumping = false;
    }

    public void Jump()
    {
        animator.SetBool("IsJumping", true);
        isJumping = true;
    }
}
