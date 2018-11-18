using System.Collections.Generic;
using UnityEngine;

public class DirectionsAllowed : MonoBehaviour
{
    private static string PlayPiece = "PlayPiece";

    private Dictionary<Vector3, Vector3> _directions = new Dictionary<Vector3, Vector3>();

    public DirectionLines lines;
    
    public bool IsAvailable(Vector3 direction)
    {
        return _directions.ContainsKey(direction);
    }

    public Vector3 Get(Vector3 direction)
    {
        return _directions[direction];
    }

    public void TurnOn(GameObject piece)
    {
        lines.Clear();
        _directions.Clear();

        AddLine(piece, Vector3.forward);
        AddLine(piece, Vector3.back);
        AddLine(piece, Vector3.left);
        AddLine(piece, Vector3.right);
    }

    public void TurnOff()
    {
        lines.Clear();
    }

    private void AddLine(GameObject piece, Vector3 direction)
    {
        RaycastHit hitInfo = new RaycastHit();
        int layerMask = 1 << LayerMask.NameToLayer(PlayPiece);
        if (Physics.Raycast(piece.transform.position + direction, direction, out hitInfo, 5, layerMask))
        {
            lines.AddLine(piece.transform.position + (direction * 0.5f),
                          hitInfo.collider.gameObject.transform.position - (direction * 0.5f));
            _directions.Add(direction, hitInfo.collider.gameObject.transform.position - direction);
        }
    }
}
