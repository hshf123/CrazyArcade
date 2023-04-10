using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

public class Connector
{
    Func<Session> _sessionFactory;

    public void Connect(string serverIP, int serverPort, Func<Session> sessionFactory, int count = 1)
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
            Console.WriteLine(e.ToString());
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
            Console.WriteLine($"OnConnectCompleted Fail: {args.SocketError}");
        }
    }
}
