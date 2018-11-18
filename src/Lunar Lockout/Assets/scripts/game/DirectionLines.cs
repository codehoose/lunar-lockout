using UnityEngine;

public class DirectionLines : MonoBehaviour
{
    int _index = 0;
    public LineRenderer[] lines;
    public float yOffset = 0.26f;

    public void Clear()
    {
        foreach(var line in lines)
        {
            line.gameObject.SetActive(false);
        }

        _index = 0;
    }

    public void AddLine(Vector3 start, Vector3 end)
    {
        var newStart = start;
        var newEnd = end;
        
        newEnd.y = yOffset;
        newStart.y = yOffset;

        var line = lines[_index++];
        line.SetPosition(0, newStart);
        line.SetPosition(1, newEnd);
        line.gameObject.SetActive(true);

        var size = (int)((start - end).magnitude);
        line.GetComponent<Trundle>().SetSize(size);
    }
}
