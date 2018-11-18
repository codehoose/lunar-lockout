using System;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class BoardCreate : MonoBehaviour
{
    private bool _nextLevel = false;
    public static string CurrentBoard = "CurrentBoard";

    private Dictionary<char, GameObject> _pieces = new Dictionary<char, GameObject>();

    private Vector3 _topLeft = new Vector3(-2, 0, 2);

    public GameObject blue;
    public GameObject green;
    public GameObject orange;
    public GameObject purple;
    public GameObject yellow;
    public GameObject astronaut;

    public TextMeshProUGUI levelText;

    void Awake()
    {
        _pieces['b'] = blue;
        _pieces['g'] = green;
        _pieces['o'] = orange;
        _pieces['p'] = purple;
        _pieces['y'] = yellow;
        _pieces['r'] = astronaut;
    }

    public void LoadBoard(int boardId)
    {
        var board = Resources.Load<TextAsset>(boardId.ToString()).text;
        var lines = board.Split("\r\n".ToCharArray(), StringSplitOptions.RemoveEmptyEntries);

        for (int i = 0; i < lines.Length; i++)
        {
            var line = lines[i];

            for (int p = 0; p < line.Length; p++)
            {
                var ch = line[p];
                if (ch == '-')
                    continue;

                _pieces[ch].transform.position = _topLeft + new Vector3(p, 0, -i);
            }
        }
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            MessageQueue.Instance.SendMessage(QuitToMenuMessage.Instance);
        }
    }

    void Start()
    {
        MessageQueue.Instance.AddRecipient<AstronautIsSpaceShipMessage>(NextLevel);
        var currentBoard = PlayerPrefs.GetInt(CurrentBoard, 1);
        levelText.text = currentBoard.ToString();
        LoadBoard(currentBoard);

        MessageQueue.Instance.SendMessage(GameStartMessage.Instance);
    }

    private void NextLevel(IMessage message)
    {
        if (_nextLevel)
            return;

        _nextLevel = true;
        var currentBoard = PlayerPrefs.GetInt(CurrentBoard, 1);
        currentBoard++;

        var levelName = "Game";

        if (currentBoard == 11)
        {
            currentBoard = 1;
            levelName = "Finished";
        }

        PlayerPrefs.SetInt(CurrentBoard, currentBoard);
        MessageQueue.Instance.SendMessage(new MoveToNextLevelMessage(levelName));
    }
}
