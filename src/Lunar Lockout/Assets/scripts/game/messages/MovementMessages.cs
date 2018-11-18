public class CursorMoveMessage : IMessage
{
    public static CursorMoveMessage Instance = new CursorMoveMessage();
}

public class PieceMoveMessage : IMessage
{
    public static PieceMoveMessage Instance = new PieceMoveMessage();
}

public class EnterSpaceShipMessage : IMessage
{
    public static EnterSpaceShipMessage Instance = new EnterSpaceShipMessage();
}

public class AstronautIsSpaceShipMessage : IMessage
{
    public static AstronautIsSpaceShipMessage Instance = new AstronautIsSpaceShipMessage();
}