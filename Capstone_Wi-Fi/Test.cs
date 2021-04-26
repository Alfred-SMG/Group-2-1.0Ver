using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using UnityEngine;
using UnityEngine.UI;

public class Test : MonoBehaviour
{

    /// <summary>
    /// 场景上的文本框用来显示android发送过来的内容
    /// </summary>

    /// <summary>
    /// android原生代码对象
    /// </summary>
    AndroidJavaObject _u2a;
    bool isOn = false;

    void Start()
    {
        //通过该API来实例化导入的arr中对应的类
        _u2a = new AndroidJavaObject("com.wku.unitylib.Unity2Android");
        Button butt = (Button)this.GetComponent<Button>();
        butt.onClick.AddListener(ButtonOnClickEvent);
        //_net = new AndroidJavaObject("com.wku.unitylib.UDP");
        _u2a.Call<bool>("listen");
    }
    public void ButtonOnClickEvent()
    {
        bool success = _u2a.Call<bool>("showToast", "this is unity");
        if (true == success)
        {
            Encoding utf8Encoding = System.Text.Encoding.UTF8;
            if (!isOn) { 
                _u2a.Call<bool>("sendBytes", utf8Encoding.GetBytes("LED_ON"));
                isOn = true;
            }
            else if (isOn)
            {
                _u2a.Call<bool>("sendBytes", utf8Encoding.GetBytes("LED_OFF"));
                isOn = false;
            }
               
            //success = _u2a.Call<bool>("showToast", "hello world");
            //_net.Call("send","hello world\r");
        }
    }

    void Update()
    {

    }

    /// <summary>
    /// 场景上按点击时触发该方法
    /// </summary>



    /// <summary>
    /// 原生层通过该方法传回信息
    /// </summary>
    /// <param name="content"></param>

}
