using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;

public class NetworkManager
{
    public ServerSessionManager SessionManager { get; private set; } = new ServerSessionManager();

    public void Init()
    {
        Connector connector = new Connector();
        connector.Connect(
            "127.0.0.1",
            5959,
            () => { return new ServerSession(); },
            1);
    }
}
