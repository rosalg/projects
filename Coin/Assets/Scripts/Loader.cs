using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Loader : MonoBehaviour
{
    public GameObject gameManager = null;
    public GameObject canvasManager = null;
    public GameObject audioManager = null;

    void Awake()
    {
        if (SceneManager.GetActiveScene().buildIndex != 0)
        {
            if (GameManager.instance == null)
            {
                Instantiate(gameManager);
            }
            if (CanvasManager.instance == null)
            {
                Instantiate(canvasManager);
            }
        }
        
        if(AudioManager.instance == null)
        {
            Instantiate(audioManager);
        }
     }
}
