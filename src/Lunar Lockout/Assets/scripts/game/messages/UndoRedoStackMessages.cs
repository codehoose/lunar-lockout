public class UndoCommandMessage : IMessage
{
    public static UndoCommandMessage Instance = new UndoCommandMessage();
}

public class RedoCommandMessage : IMessage
{
    public static RedoCommandMessage Instance = new RedoCommandMessage();
}
