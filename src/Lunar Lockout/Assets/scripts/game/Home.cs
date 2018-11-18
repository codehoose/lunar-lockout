using System.Collections;
using UnityEngine;

public class Home : MonoBehaviour
{
    private bool _dropping = false;
    private float _start = 0f;

    public GameObject homeTile;

    public Cursor cursor;

    public void OnTriggerStay(Collider other)
    {
        if (_dropping || other.GetComponent<Astronaut>() == null)
            return;

        if (Time.time > _start + 0.5f)
            StartCoroutine(DropAstronaut(other.transform));
    }

    public void OnTriggerEnter(Collider other)
    {
        if (other.GetComponent<Astronaut>() == null)
            return;

        _start = Time.time;
    }

    private IEnumerator DropAstronaut(Transform t)
    {
        cursor.noMove = true;

        yield return new WaitForSeconds(2); // TODO: WAIT?!?!

        MessageQueue.Instance.SendMessage(EnterSpaceShipMessage.Instance);

        var target = t.position + Vector3.down * 3;
        var start = t.position;

        var hs = homeTile.transform.position;
        var he = hs + Vector3.down * 3;

        float time = 0f;
        while (time < 1f)
        {
            t.position = Vector3.Lerp(start, target, time);
            homeTile.transform.position = Vector3.Lerp(hs, he, time);
            time += Time.deltaTime;// / 0.5f;
            yield return null;
        }

        homeTile.transform.position = he;
        t.position = target;

        MessageQueue.Instance.SendMessage(AstronautIsSpaceShipMessage.Instance);
    }
}
