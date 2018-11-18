using UnityEngine;

public class Trundle : MonoBehaviour
{
    float x = 0f;

    public void SetSize(int size)
    {
        //var scale = 4 - size;

        //var material = GetComponent<LineRenderer>().material;
        //material.mainTextureScale = new Vector2(scale, 1);
    }

    void Update()
    {
        x -= Time.deltaTime / 1.5f;
        x = Mathf.Repeat(x, 1f);
        var offset = new Vector2(x, 0);

        var material = GetComponent<LineRenderer>().material;
        material.mainTextureOffset = offset;
    }
}
