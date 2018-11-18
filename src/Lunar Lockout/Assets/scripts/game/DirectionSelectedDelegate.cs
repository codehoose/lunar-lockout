using System;
using UnityEngine;

public delegate void DirectionSelectedDelegate(object sender, DirectionSelectedEventArgs e);

public class DirectionSelectedEventArgs : EventArgs
{
    public Vector3 Direction { get; private set; }

    public DirectionSelectedEventArgs(Vector3 direction)
    {
        Direction = direction;
    }
}
