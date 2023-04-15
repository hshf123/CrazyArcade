using System;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;
using UnityEngine;

public class Connector
{
    Func<Session> _sessionFactory;

    async public Task Connect(string serverIP, int serverPort, Func<Session> sessionFactory, int count = 1)
    {
        for (int i = 0; i < count; i++)
        {
            // 휴대폰 설정
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            _sessionFactory = sessionFactory;

            SocketAsyncEventArgs args = new SocketAsyncEventArgs();
            args.RemoteEndPoint = new IPEndPoint(IPAddress.Parse(serverIP), serverPort);
            args.UserToken = socket;

            RegisterConnect(args);
        }
    }

    async Task RegisterConnect(SocketAsyncEventArgs args)
    {
        Socket socket = args.UserToken as Socket;
        if (socket == null)
            return;
        try
        {
            await socket.ConnectAsync(args.RemoteEndPoint);
        }
        catch (SocketException e)
        {
            Debug.Log(e.ToString());
            return;
        }
        OnConnectCompleted(args);
    }

    void OnConnectCompleted(SocketAsyncEventArgs args)
    {
        if (args.SocketError == SocketError.Success)
        {
            Session session = _sessionFactory.Invoke();
            session.Start(args.UserToken as Socket);
            session.OnConnected(args.RemoteEndPoint);
        }
        else
        {
            Debug.Log($"OnConnectCompleted Fail: {args.SocketError}");
        }
    }
}
