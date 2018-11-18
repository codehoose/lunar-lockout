using UnityEngine;

public class MovePieceCommand : ICommand
{
    private GameObject _piece;
    private Vector3 _start;
    private Vector3 _end;

    public MovePieceCommand(GameObject piece, Vector3 start, Vector3 end)
    {
        _piece = piece;
        _start = start;
        _end = end;
    }

    public void Execute()
    {
        _piece.GetComponent<SlidePiece>().Move(_start, _end);
    }

    public void Undo()
    {
        _piece.GetComponent<SlidePiece>().Move(_end, _start);
    }
}