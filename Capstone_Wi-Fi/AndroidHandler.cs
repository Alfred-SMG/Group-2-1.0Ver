using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class AndroidHandler : MonoBehaviour
{
    public Text buttonText;
    public Text receiveText;
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    public void FromAndroid(string content)
    {
        buttonText.text = content;
    }

    public void Receive(string content)
    {
        receiveText.text = content;
        if (content.CompareTo("press")==0)
        {
            GameObject.Find("WinText").GetComponent<GhostMainControl>().SetPress();
        }
        else { }
    }
}
