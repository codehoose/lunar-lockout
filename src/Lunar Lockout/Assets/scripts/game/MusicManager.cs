using System;
using UnityEngine;
using UnityEngine.Audio;

public class MusicManager : MonoBehaviour
{
    public static string NoMusic = "NoMusic";
    public static string FullMix = "FullMix";

    public AudioMixer audioMixer;

    private void Awake()
    {
        MessageQueue.Instance.AddRecipient<EnterSpaceShipMessage>(FadeOutMusic);
        MessageQueue.Instance.AddRecipient<QuitToMenuMessage>(FadeOutMusic);
        MessageQueue.Instance.AddRecipient<GameStartMessage>(StartAudio);
    }

    private void StartAudio(GameStartMessage obj)
    {
        var fullMix = audioMixer.FindSnapshot(FullMix);
        fullMix.TransitionTo(1f);
    }

    private void FadeOutMusic(IMessage message)
    {
        var noMusic = audioMixer.FindSnapshot(NoMusic);
        noMusic.TransitionTo(1f);
    }
}
