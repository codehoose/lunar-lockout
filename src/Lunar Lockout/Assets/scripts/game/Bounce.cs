using System.Collections;
using UnityEngine;

public class Bounce : MonoBehaviour
{
    private IEnumerator _bounce = null;

    public Vector3 start = Vector3.zero;
    public Vector3 end = Vector3.up;

    [HideInInspector]
    public bool bouncing;

    public void StartIt()
    {
        StopIt();
        bouncing = true;
        _bounce = DoBounce();
        StartCoroutine(_bounce);
    }

    public void StopIt()
    {
        bouncing = false;

        if (_bounce == null)
            return;

        if (_bounce != null)
        {
            StopCoroutine(_bounce);
            var vec = transform.position;
            vec.y = 0;
            transform.position = vec;
        }
    }

    private IEnumerator DoBounce()
    {
        float duration = 0.25f;

        var s = start;
        var e = end;
        bool flip = false;

        var pos = transform.position;

        while (true)
        {
            float time = 0f;
            while (time < 1f)
            {
                transform.position = pos + Vector3.Lerp(s, e, time);
                time += Time.deltaTime / duration;
                yield return null;
            }

            flip = !flip;
            s = flip ? end : start;
            e = flip ? start : end;
        }
    }
}
