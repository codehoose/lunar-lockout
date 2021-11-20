public class VolumeUpMessage : IMessage
{
    public static VolumeUpMessage Instance = new VolumeUpMessage();
}

public class VolumeDownMessage: IMessage
{
    public static VolumeDownMessage Instance = new VolumeDownMessage();
}

public class VolumeLevelMessage :IMessage
{
    public float VolumeLevel { get; private set; }

    public VolumeLevelMessage(float volumeLevelPercent)
    {
        VolumeLevel = volumeLevelPercent;
    }
}