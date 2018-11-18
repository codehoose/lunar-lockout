using System;
using System.Collections.Generic;
using UnityEngine;

public class MessageQueue : MonoBehaviour
{
    #region Singleton

    private static MessageQueue _instance;

    public static MessageQueue Instance
    {
        get
        {
            if (_instance == null)
            {
                _instance = FindObjectOfType<MessageQueue>();
                if (_instance==null)
                {
                    var go = new GameObject("~~~ MESSAGE QUEUE ~~~");
                    _instance = go.AddComponent<MessageQueue>();
                }
            }

            return _instance;
        }
    }

    #endregion

    private Dictionary<Type, List<IRecipient>> _recipients = new Dictionary<Type, List<IRecipient>>();
    
    public void AddRecipient<T>(IRecipient recipient) where T: IMessage
    {
        List<IRecipient> list = null;
        if (!_recipients.TryGetValue(typeof(T), out list))
        {
            list = new List<IRecipient>();
            _recipients[typeof(T)] = list;
        }

        list.Add(recipient);
    }

    public void AddRecipient<T>(Action<T> recipient) where T: IMessage
    {
        var actionRecipient = new ActionRecipient<T>(recipient);
        AddRecipient<T>(actionRecipient);
    }

    public void SendMessage(IMessage message)
    {
        List<IRecipient> list = null;
        if (_recipients.TryGetValue(message.GetType(), out list))
        {
            foreach (var recipient in list)
            {
                recipient.Receive(message);
            }
        }
    }
}
