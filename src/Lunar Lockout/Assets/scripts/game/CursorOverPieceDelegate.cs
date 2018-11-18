using System;
using UnityEngine;

public delegate void CursorOverPieceDelegate(object sender, PieceEventArgs e);

public class PieceEventArgs : EventArgs
{
    public GameObject Piece { get; private set; }

    public PieceEventArgs(GameObject piece)
    {
        Piece = piece;
    }
}