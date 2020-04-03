using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.EventSystems;

public class GameManager : MonoBehaviour, ISelectHandler
{
    public static GameManager instance = null;
    public GameObject exitB;
    public GameObject exitW;
    [HideInInspector]
    public string currentLevel;
    [HideInInspector]
    public Vector3 positionPlayerB;
    [HideInInspector]
    public Vector3 positionPlayerW;
    [HideInInspector]
    public bool isLoading;

    private Collider2D[] collidersB = new Collider2D[5];
    private Collider2D[] collidersW = new Collider2D[5];
    private ContactFilter2D filter;
    

    private void Awake()
    {
        SceneManager.sceneLoaded += OnSceneLoaded;
    }

    void OnSceneLoaded(Scene scene, LoadSceneMode mode)
    {
        if (instance == null)
        {
            instance = this;
        }
        else if (instance != this)
        {
            Destroy(gameObject);
            return;
        }
        DontDestroyOnLoad(gameObject);
        
        filter = new ContactFilter2D
        {
            layerMask = 8
        };
        exitB = GameObject.Find("BExit");
        exitW = GameObject.Find("WExit");
        currentLevel = SceneManager.GetActiveScene().name;
    }
    
    void Update()
    {
        if (isLoading)
        {
            return;
        }

        Collider2D colliderB = GameObject.Find("PlayerB").GetComponent<BoxCollider2D>();
        Collider2D colliderW = GameObject.Find("PlayerW").GetComponent<BoxCollider2D>();

        if (exitB.GetComponent<BoxCollider2D>().IsTouching(colliderB) && exitW.GetComponent<BoxCollider2D>().IsTouching(colliderW))
        {
            isLoading = true;
            AudioManager.instance.Play("VictorySound");
            StartCoroutine(NextLevel());
        }

        positionPlayerB = GameObject.Find("PlayerB").transform.position;
        positionPlayerW = GameObject.Find("PlayerW").transform.position;
        SaveSystem.SaveLevel(this);
    }
    

    public void Restart()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }

    public void OnSelect(BaseEventData eventData)
    {
        Debug.Log(eventData.currentInputModule);
        
    }

    IEnumerator NextLevel()
    {
        yield return new WaitForSeconds(1f);
        isLoading = false;
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
    }
}
