using System;
using System.Collections;
using UnityEngine;

public class ObjectSelection : MonoBehaviour
{
    public Cursor cursor;
    private GameObject _piece;
    private DirectionsAllowed _directions;

    void Awake()
    {
        _directions = GetComponent<DirectionsAllowed>();
        cursor.CursorOverPiece += Cursor_CursorOverPiece;
        cursor.CursorExitPiece += Cursor_CursorExitPiece;
        cursor.DirectionSelected += Cursor_DirectionSelected;
    }

    private void Cursor_DirectionSelected(object sender, DirectionSelectedEventArgs e)
    {
        if (!cursor.noMove || _piece == null || !_directions.IsAvailable(e.Direction))
            return;

        _piece.GetComponent<Bounce>().StopIt();
        _directions.TurnOff();
        cursor.MoveAllowed();
        // TODO: MOVE PIECE!
        var newPos = _directions.Get(e.Direction);

        UndoRedoStack.Instance.Add(new MovePieceCommand(_piece, _piece.transform.position, newPos));
        //StartCoroutine(MovePiece(_piece, newPos));
        
        _piece = null;
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            if (_piece != null)
            {
                if (_piece.GetComponent<Bounce>().bouncing)
                {
                    _directions.TurnOff();
                    _piece.GetComponent<Bounce>().StopIt();
                    cursor.noMove = false;
                }
                else
                {
                    cursor.noMove = true;
                    _piece.GetComponent<Bounce>().StartIt();
                    _directions.TurnOn(_piece);
                }
            }
        }
    }

    private void Cursor_CursorExitPiece(object sender, PieceEventArgs e)
    {
        _piece = null;
    }

    private void Cursor_CursorOverPiece(object sender, PieceEventArgs e)
    {
        _piece = e.Piece;
    }
}
