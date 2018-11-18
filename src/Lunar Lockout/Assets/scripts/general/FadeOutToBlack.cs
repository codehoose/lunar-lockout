using System;
using System.Collections;
using UnityEngine;
using UnityEngine.Audio;

public class FadeOutToBlack : MonoBehaviour
{
    public AudioMixer audioMixer;

    public void Fader(Action action, float start = 0, float end = 1)
    {
        StartCoroutine(FadeOut(action, start, end));
    }

    private IEnumerator FadeOut(Action action, float start, float end, string snapshot = "")
    {
        var fadeOut = GetComponent<CanvasGroup>();

        AudioMixerSnapshot musicFade = null;
        if (!string.IsNullOrEmpty(snapshot))
        {
            musicFade = audioMixer.FindSnapshot(snapshot);
            musicFade.TransitionTo(1f);
        }

        float time = 0f;
        while (time < 1f)
        {
            fadeOut.alpha = Mathf.Lerp(start, end, time);
            time += Time.deltaTime;
            yield return null;
        }

        fadeOut.alpha = end;

        if (action != null)
            action.Invoke();
    }
}
