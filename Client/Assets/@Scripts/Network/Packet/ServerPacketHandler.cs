using Google.Protobuf;
using Google.Protobuf.Protocol;
using System;
using System.Collections.Generic;

public enum MsgId : ushort
{
	PKT_C_LOGIN = 1000,
	PKT_S_LOGIN = 1001,
	PKT_C_CHANNELCHOICE = 1002,
	PKT_S_CHANNELCHOICE = 1003,
	PKT_C_CHANNELCHAT = 1004,
	PKT_S_CHANNELCHAT = 1005,
	PKT_C_MAKEROOM = 1006,
	PKT_S_MAKEROOM = 1007,
	PKT_S_CHANNELUPDATE = 1008,
	PKT_C_ROOMENTER = 1009,
	PKT_S_ROOMENTER = 1010,
	PKT_S_ROOMUPDATE = 1011,
	PKT_C_ROOMREADY = 1012,
	PKT_C_ROOMSTART = 1013,
	PKT_S_ROOMSTART = 1014,
	PKT_C_MOVE = 1015,
	PKT_S_MOVE = 1016,
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
        _onRecv.Add((ushort)MsgId.PKT_S_CHANNELCHOICE, MakePacket<S_CHANNELCHOICE>);
        _handler.Add((ushort)MsgId.PKT_S_CHANNELCHOICE, PacketHandler.S_CHANNELCHOICEHandler);
        _onRecv.Add((ushort)MsgId.PKT_S_CHANNELCHAT, MakePacket<S_CHANNELCHAT>);
        _handler.Add((ushort)MsgId.PKT_S_CHANNELCHAT, PacketHandler.S_CHANNELCHATHandler);
        _onRecv.Add((ushort)MsgId.PKT_S_MAKEROOM, MakePacket<S_MAKEROOM>);
        _handler.Add((ushort)MsgId.PKT_S_MAKEROOM, PacketHandler.S_MAKEROOMHandler);
        _onRecv.Add((ushort)MsgId.PKT_S_CHANNELUPDATE, MakePacket<S_CHANNELUPDATE>);
        _handler.Add((ushort)MsgId.PKT_S_CHANNELUPDATE, PacketHandler.S_CHANNELUPDATEHandler);
        _onRecv.Add((ushort)MsgId.PKT_S_ROOMENTER, MakePacket<S_ROOMENTER>);
        _handler.Add((ushort)MsgId.PKT_S_ROOMENTER, PacketHandler.S_ROOMENTERHandler);
        _onRecv.Add((ushort)MsgId.PKT_S_ROOMUPDATE, MakePacket<S_ROOMUPDATE>);
        _handler.Add((ushort)MsgId.PKT_S_ROOMUPDATE, PacketHandler.S_ROOMUPDATEHandler);
        _onRecv.Add((ushort)MsgId.PKT_S_ROOMSTART, MakePacket<S_ROOMSTART>);
        _handler.Add((ushort)MsgId.PKT_S_ROOMSTART, PacketHandler.S_ROOMSTARTHandler);
        _onRecv.Add((ushort)MsgId.PKT_S_MOVE, MakePacket<S_MOVE>);
        _handler.Add((ushort)MsgId.PKT_S_MOVE, PacketHandler.S_MOVEHandler);
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