using Google.Protobuf;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class ServerSessionManager
{
    List<ServerSession> _sessions = new List<ServerSession>();
    object _lock = new object();

    public void Add(ServerSession session)
    {
        lock (_lock)
        {
            _sessions.Add(session);
        }
    }

    public void Remove(ServerSession session)
    {
        lock(_lock)
        {
            _sessions.Remove(session);
        }
    }

    public void Broadcast(IMessage packet)
    {
        lock (_lock)
        {
            foreach (ServerSession session in _sessions)
            {
                session.Send(packet);
            }
        }
    }
}
