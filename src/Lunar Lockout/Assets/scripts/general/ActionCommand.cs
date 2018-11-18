using System;

public class ActionCommand : ICommand
{
    private Action _execute = null;
    private Action _undo = null;

    public ActionCommand(Action execute, Action undo)
    {
        _execute = execute;
        _undo = undo;
    }

    public void Execute()
    {
        if (_execute != null)
            _execute.Invoke();
    }

    public void Undo()
    {
        if (_undo != null)
            _undo.Invoke();
    }
}
