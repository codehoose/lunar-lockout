using System.Collections.Generic;
using UnityEngine;

public class UndoRedoStack : MonoBehaviour
{
    #region Singleton

    private static UndoRedoStack _instance;

    public static UndoRedoStack Instance
    {
        get
        {
            if (_instance ==null)
            {
                _instance = FindObjectOfType<UndoRedoStack>();
                if (_instance == null)
                {
                    var go = new GameObject("~~~ UNDO REDO STACK ~~~");
                    _instance = go.AddComponent<UndoRedoStack>();
                }
            }

            return _instance;
        }
    }

    #endregion

    private Stack<ICommand> _executed = new Stack<ICommand>();

    private Stack<ICommand> _redo = new Stack<ICommand>();

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.U))
        {
            Undo();
        } else if (Input.GetKeyDown(KeyCode.R))
        {
            Redo();
        }
    }

    public void Add(ICommand command)
    {
        command.Execute();
        _executed.Push(command);
        _redo.Clear();
    }

    public void Undo()
    {
        if (_executed.Count == 0)
            return;

        MessageQueue.Instance.SendMessage(UndoCommandMessage.Instance);

        var command = _executed.Pop();
        command.Undo();
        _redo.Push(command);
    }

    public void Redo()
    {
        if (_redo.Count == 0)
            return;

        MessageQueue.Instance.SendMessage(RedoCommandMessage.Instance);

        var command = _redo.Pop();
        command.Execute();
        _executed.Push(command);
    }
}
