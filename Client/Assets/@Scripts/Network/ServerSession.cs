using Google.Protobuf;
using System;
using System.Net;
using UnityEngine;

public class ServerSession : PacketSession
{
    public override void OnConnected(EndPoint endPoint)
    {
        Debug.Log($"OnConnected : {endPoint}");
        Managers.Net.SessionManager.Add(this);
        Managers.Scene.ChangeScene<LoginScene>(Define.SceneType.LoginScene);
    }

    public override void OnDisconnected(EndPoint endPoint)
    {
        Debug.Log($"OnDisconnected : {endPoint}");
        Managers.Net.SessionManager.Remove(this);
    }

    public override void OnRecvPacket(ArraySegment<byte> buffer)
    {
        // TODO : packetId 대역 체크
        PacketManager.Instance.OnRecvPacket(this, buffer);
    }

    public override void OnSend(int numOfBytes)
    {
    }
}
