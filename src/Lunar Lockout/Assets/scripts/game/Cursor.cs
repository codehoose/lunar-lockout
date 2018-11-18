using System;
using System.Collections;
using UnityEngine;

public class Cursor : MonoBehaviour
{
    public static string PlayPiece = "PlayPiece";

    private bool _moving = false;

    public event CursorOverPieceDelegate CursorOverPiece;

    public event CursorOverPieceDelegate CursorExitPiece;

    public event DirectionSelectedDelegate DirectionSelected;

    public bool noMove;

    void Update()
    {
        if (_moving)
            return;

        var newPos = Vector3.zero;

        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow))
        {
            newPos += Vector3.left;
            if (DirectionSelected != null)
                DirectionSelected(this, new DirectionSelectedEventArgs(Vector3.left));
        }
        else if (Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow))
        {
            newPos += Vector3.right;
            if (DirectionSelected != null)
                DirectionSelected(this, new DirectionSelectedEventArgs(Vector3.right));
        }
        else if (Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.UpArrow))
        {
            newPos += Vector3.forward;
            if (DirectionSelected != null)
                DirectionSelected(this, new DirectionSelectedEventArgs(Vector3.forward));
        }
        else if (Input.GetKey(KeyCode.S) || Input.GetKey(KeyCode.DownArrow))
        {
            newPos += Vector3.back;
            if (DirectionSelected != null)
                DirectionSelected(this, new DirectionSelectedEventArgs(Vector3.back));
        }

        var target = transform.position + newPos;

        if (noMove || newPos == Vector3.zero || target.x < -2 || target.x > 2 || target.z > 2 || target.z < -2)
            return;

        MessageQueue.Instance.SendMessage(CursorMoveMessage.Instance);
        StartCoroutine(Move(transform.position, target));
    }

    public void MoveAllowed()
    {
        StartCoroutine(ToggleMove(true));
    }

    private IEnumerator ToggleMove(bool move)
    {
        yield return null;
        Input.ResetInputAxes();
        yield return null;

        noMove = !move;
    }

    private IEnumerator Move(Vector3 source, Vector3 target)
    {
        _moving = true;
        float speed = 0.1f;

        float time = 0f;
        while (time <1f)
        {
            transform.position = Vector3.Lerp(source, target, time);
            time += Time.deltaTime / speed;
            yield return null;
        }

        transform.position = target;
        _moving = false;
    }

    public void OnTriggerEnter(Collider other)
    {
        if (CursorOverPiece == null || other.tag != PlayPiece)
            return;

        CursorOverPiece.Invoke(this, new PieceEventArgs(other.gameObject));
    }

    public void OnTriggerExit(Collider other)
    {
        if (CursorExitPiece == null || other.tag != PlayPiece)
            return;

        CursorExitPiece.Invoke(this, new PieceEventArgs(other.gameObject));
    }
}
