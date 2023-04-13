using Google.Protobuf;
using Google.Protobuf.Protocol;
using System;
using System.Collections.Generic;

public enum MsgId : ushort
{
	PKT_C_LOGIN = 1000,
	PKT_S_LOGIN = 1001,
	PKT_C_CHANNELCHOIC = 1002,
	PKT_S_CHANNELCHOIC = 1003,
	PKT_C_CHANNELCHAT = 1004,
	PKT_S_CHANNELCHAT = 1005,
	PKT_C_MAKEROOM = 1006,
	PKT_S_MAKEROOM = 1007,
};

class PacketManager
{
    #region Singleton
    static PacketManager _instance = new PacketManager();
    public static PacketManager Instance { get { return _instance; } }
    #endregion

    PacketManager()
    {
        Register();
    }

    Dictionary<ushort, Action<PacketSession, ArraySegment<byte>, ushort>> _onRecv = new Dictionary<ushort, Action<PacketSession, ArraySegment<byte>, ushort>>();
    Dictionary<ushort, Action<PacketSession, IMessage>> _handler = new Dictionary<ushort, Action<PacketSession, IMessage>>();

    public Action<PacketSession, IMessage, ushort> CustomHandler { get; set; }

    public void Register()
    {
        _onRecv.Add((ushort)MsgId.PKT_S_LOGIN, MakePacket<S_LOGIN>);
        _handler.Add((ushort)MsgId.PKT_S_LOGIN, PacketHandler.S_LOGINHandler);
        _onRecv.Add((ushort)MsgId.PKT_S_CHANNELCHOIC, MakePacket<S_CHANNELCHOIC>);
        _handler.Add((ushort)MsgId.PKT_S_CHANNELCHOIC, PacketHandler.S_CHANNELCHOICHandler);
        _onRecv.Add((ushort)MsgId.PKT_S_CHANNELCHAT, MakePacket<S_CHANNELCHAT>);
        _handler.Add((ushort)MsgId.PKT_S_CHANNELCHAT, PacketHandler.S_CHANNELCHATHandler);
        _onRecv.Add((ushort)MsgId.PKT_S_MAKEROOM, MakePacket<S_MAKEROOM>);
        _handler.Add((ushort)MsgId.PKT_S_MAKEROOM, PacketHandler.S_MAKEROOMHandler);
    }

    public void OnRecvPacket(PacketSession session, ArraySegment<byte> buffer)
    {
        ushort count = 0;

        ushort size = BitConverter.ToUInt16(buffer.Array, buffer.Offset);
        count += 2;
        ushort id = BitConverter.ToUInt16(buffer.Array, buffer.Offset + count);
        count += 2;

        Action<PacketSession, ArraySegment<byte>, ushort> action = null;
        if (_onRecv.TryGetValue(id, out action))
            action.Invoke(session, buffer, id);
    }

    void MakePacket<T>(PacketSession session, ArraySegment<byte> buffer, ushort id) where T : IMessage, new()
    {
        T pkt = new T();
        pkt.MergeFrom(buffer.Array, buffer.Offset + 4, buffer.Count - 4);

        if (CustomHandler != null)
        {
            CustomHandler.Invoke(session, pkt, id);
        }
        else
        {
            Action<PacketSession, IMessage> action = null;
            if (_handler.TryGetValue(id, out action))
                action.Invoke(session, pkt);
        }
    }

    public Action<PacketSession, IMessage> GetPacketHandler(ushort id)
    {
        Action<PacketSession, IMessage> action = null;
        if (_handler.TryGetValue(id, out action))
            return action;
        return null;
    }
}