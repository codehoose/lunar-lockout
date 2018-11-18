using System;
using UnityEngine;
using UnityEngine.SceneManagement;

public class FadeManager : MonoBehaviour
{
    public FadeOutToBlack fadeToBlack;

    void Awake()
    {
        MessageQueue.Instance.AddRecipient<GameStartMessage>(GameStart);
        MessageQueue.Instance.AddRecipient<QuitToMenuMessage>(LoadScene);
        MessageQueue.Instance.AddRecipient<MoveToNextLevelMessage>(LoadNextLevel);
    }

    private void GameStart(GameStartMessage obj)
    {
        fadeToBlack.Fader(null, 1, 0);
    }

    private void LoadNextLevel(MoveToNextLevelMessage nextLevel)
    {
        fadeToBlack.Fader(() => SceneManager.LoadScene(nextLevel.LevelName));
    }

    private void LoadScene(QuitToMenuMessage obj)
    {
        fadeToBlack.Fader(() => SceneManager.LoadScene("MainMenu"));
    }
}
