using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class LevelData
{
    public string currentLevel;
    public float[] whitePosition = new float[3];
    public float[] blackPosition = new float[3];

    public LevelData (GameManager gameManager)
    {
        currentLevel = gameManager.currentLevel;

        whitePosition[0] = gameManager.positionPlayerW.x;
        whitePosition[1] = gameManager.positionPlayerW.y;
        whitePosition[2] = gameManager.positionPlayerW.z;

        blackPosition[0] = gameManager.positionPlayerW.x;
        blackPosition[1] = gameManager.positionPlayerW.y;
        blackPosition[2] = gameManager.positionPlayerW.z;
    }

}
