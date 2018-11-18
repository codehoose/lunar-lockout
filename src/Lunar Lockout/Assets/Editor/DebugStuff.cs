using UnityEditor;
using UnityEngine;

public static class DebugStuff
{
    [MenuItem("Lunar Lockout/Reset Current Board")]
    public static void ResetCurrentLevel()
    {
        PlayerPrefs.SetInt(BoardCreate.CurrentBoard, 1);
    }
}
