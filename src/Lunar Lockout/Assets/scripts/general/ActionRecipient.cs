using System;

public class ActionRecipient<T> : IRecipient where T: IMessage
{
    private Action<T> _action;

    public ActionRecipient(Action<T> action)
    {
        _action = action;
    }

    public void Receive(T message)
    {
        if (_action != null)
            _action(message);
    }

    void IRecipient.Receive(IMessage message)
    {
        Receive((T)message);
    }
}
