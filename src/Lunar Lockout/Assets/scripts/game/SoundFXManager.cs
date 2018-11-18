using System;
using System.Collections.Generic;
using UnityEngine;

public class SoundFXManager : MonoBehaviour
{
    private Dictionary<Type, AudioClip> _clipMap = new Dictionary<Type, AudioClip>();
    private IMessage _lastMessage = null;

    public AudioClip cursorMove;
    public AudioClip pieceMove;
    public AudioClip undo;
    public AudioClip redo;
    public AudioClip enterSpaceShip;
    
    private void Awake()
    {
        Add<CursorMoveMessage>(cursorMove);
        Add<UndoCommandMessage>(undo);
        Add<RedoCommandMessage>(redo);
        Add<PieceMoveMessage>(pieceMove);
        Add<EnterSpaceShipMessage>(enterSpaceShip);
    }

    private void Add<T>(AudioClip audioClip) where T: IMessage
    {
        _clipMap[typeof(T)] = audioClip;
        MessageQueue.Instance.AddRecipient<T>(m => PlaySound(m));
    }

    private void PlaySound(IMessage soundMessage)
    {
        if (_lastMessage != null && (_lastMessage is UndoCommandMessage || _lastMessage is RedoCommandMessage) && soundMessage is PieceMoveMessage)
        {
            _lastMessage = null;
            return;
        }

        GetComponent<AudioSource>().PlayOneShot(_clipMap[soundMessage.GetType()]);
        _lastMessage = soundMessage;
    }
}
