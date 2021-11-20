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
        MessageQueue.Instance.AddRecipient<VolumeUpMessage>(VolumeUp);
        MessageQueue.Instance.AddRecipient<VolumeDownMessage>(VolumeDown);
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

    private void VolumeUp(IMessage message)
    {
        ChangeVolume(-80, -10, 7);
    }

    private void VolumeDown(IMessage message)
    {
        ChangeVolume(-80, -10, -7);
    }

    private void ChangeVolume(float min, float max, float delta)
    {
        var current = min;
        audioMixer.GetFloat("MasterVolume", out current);
        current += delta;
        current = Mathf.Clamp(current, min, max);
        audioMixer.SetFloat("MasterVolume", current);

        var currentAsPc = Mathf.Abs(current / 70f);

        MessageQueue.Instance.SendMessage(new VolumeLevelMessage(currentAsPc));
    }
}
