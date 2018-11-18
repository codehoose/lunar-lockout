public class GameStartMessage : IMessage
{
    public static GameStartMessage Instance = new GameStartMessage();
}

public class QuitToMenuMessage : IMessage
{
    public static QuitToMenuMessage Instance = new QuitToMenuMessage();
}

public class MoveToNextLevelMessage : IMessage
{
    public string LevelName { get; set; }

    public MoveToNextLevelMessage(string levelName)
    {
        LevelName = levelName;
    }
}