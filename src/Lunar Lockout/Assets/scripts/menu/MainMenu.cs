using System;
using System.Collections;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class MainMenu : MonoBehaviour
{
    private bool _busy = false;

    public Button play;
    public Button about;
    public Button quit;

    public CanvasGroup fadeOut;
    
	IEnumerator Start ()
    {
        yield return null;
        EventSystem.current.SetSelectedGameObject(null);
        yield return null;
        EventSystem.current.SetSelectedGameObject(play.gameObject);
    }

    public void LoadScene(string scene)
    {
        if (_busy)
            return;

        _busy = true;
        FadeOut(() => SceneManager.LoadScene(scene));
    }

    private void FadeOut(Action action)
    {
        StartCoroutine(FadeToBlack(action));
    }

    private IEnumerator FadeToBlack(Action action)
    {
        float time = 0f;
        while (time < 1f)
        {
            fadeOut.alpha = time;
            time += Time.deltaTime;
            yield return null;
        }

        fadeOut.alpha = 1f;
        action.Invoke();
    }
}
