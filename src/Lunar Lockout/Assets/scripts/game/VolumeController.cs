using System.Collections;
using UnityEngine;

public class VolumeController : MonoBehaviour
{
    public void Awake()
    {
        MessageQueue.Instance.AddRecipient<VolumeLevelMessage>(UpdateUI);
    }

    public void Update()
    {
        if (Input.GetKeyDown(KeyCode.Minus))
        {
            MessageQueue.Instance.SendMessage(VolumeDownMessage.Instance);
        }
        else if (Input.GetKeyDown(KeyCode.Equals))
        {
            MessageQueue.Instance.SendMessage(VolumeUpMessage.Instance);
        }      
    }

    private void UpdateUI(IMessage message)
    {
        StartCoroutine(UpdateTheUI());
    }

    private IEnumerator UpdateTheUI()
    {
        yield return null;
    }
}