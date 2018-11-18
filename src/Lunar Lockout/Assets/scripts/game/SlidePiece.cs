using System.Collections;
using UnityEngine;

public class SlidePiece : MonoBehaviour
{
    public bool Moving { get; private set; }

    public void Move(Vector3 start, Vector3 end)
    {
        MessageQueue.Instance.SendMessage(PieceMoveMessage.Instance);
        StartCoroutine(MovePiece(start, end));
    }

    private IEnumerator MovePiece(Vector3 start, Vector3 end)
    {
        Moving = true;
        float time = 0f;
        float duration = 0.25f;

        while (time < 1f)
        {
            transform.position = Vector3.Lerp(start, end, time);
            time += Time.deltaTime / duration;
            yield return null;
        }

        transform.position = end;
        Moving = false;
    }
}
