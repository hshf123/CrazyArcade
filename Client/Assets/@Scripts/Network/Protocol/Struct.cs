// <auto-generated>
//     Generated by the protocol buffer compiler.  DO NOT EDIT!
//     source: Struct.proto
// </auto-generated>
#pragma warning disable 1591, 0612, 3021
#region Designer generated code

using pb = global::Google.Protobuf;
using pbc = global::Google.Protobuf.Collections;
using pbr = global::Google.Protobuf.Reflection;
using scg = global::System.Collections.Generic;
namespace Protocol {

  /// <summary>Holder for reflection information generated from Struct.proto</summary>
  public static partial class StructReflection {

    #region Descriptor
    /// <summary>File descriptor for Struct.proto</summary>
    public static pbr::FileDescriptor Descriptor {
      get { return descriptor; }
    }
    private static pbr::FileDescriptor descriptor;

    static StructReflection() {
      byte[] descriptorData = global::System.Convert.FromBase64String(
          string.Concat(
            "CgxTdHJ1Y3QucHJvdG8SCFByb3RvY29sGgpFbnVtLnByb3RvIlAKB0NoYW5u",
            "ZWwSEQoJY2hhbm5lbElkGAEgASgFEhYKDm1heFBsYXllckNvdW50GAIgASgF",
            "EhoKEmN1cnJlbnRQbGF5ZXJDb3VudBgDIAEoBSJICgtDaGFubmVsSW5mbxIU",
            "CgxjaGFubmVsQ291bnQYASABKAUSIwoIY2hhbm5lbHMYAiADKAsyES5Qcm90",
            "b2NvbC5DaGFubmVsIlwKBFJvb20SDgoGcm9vbUlkGAEgASgFEhAKCHJvb21O",
            "YW1lGAIgASgJEhYKDm1heFBsYXllckNvdW50GAMgASgFEhoKEmN1cnJlbnRQ",
            "bGF5ZXJDb3VudBgEIAEoBSI9CglMb2JieUluZm8SEQoJcm9vbUNvdW50GAEg",
            "ASgFEh0KBXJvb21zGAIgAygLMg4uUHJvdG9jb2wuUm9vbWIGcHJvdG8z"));
      descriptor = pbr::FileDescriptor.FromGeneratedCode(descriptorData,
          new pbr::FileDescriptor[] { global::Protocol.EnumReflection.Descriptor, },
          new pbr::GeneratedClrTypeInfo(null, null, new pbr::GeneratedClrTypeInfo[] {
            new pbr::GeneratedClrTypeInfo(typeof(global::Protocol.Channel), global::Protocol.Channel.Parser, new[]{ "ChannelId", "MaxPlayerCount", "CurrentPlayerCount" }, null, null, null, null),
            new pbr::GeneratedClrTypeInfo(typeof(global::Protocol.ChannelInfo), global::Protocol.ChannelInfo.Parser, new[]{ "ChannelCount", "Channels" }, null, null, null, null),
            new pbr::GeneratedClrTypeInfo(typeof(global::Protocol.Room), global::Protocol.Room.Parser, new[]{ "RoomId", "RoomName", "MaxPlayerCount", "CurrentPlayerCount" }, null, null, null, null),
            new pbr::GeneratedClrTypeInfo(typeof(global::Protocol.LobbyInfo), global::Protocol.LobbyInfo.Parser, new[]{ "RoomCount", "Rooms" }, null, null, null, null)
          }));
    }
    #endregion

  }
  #region Messages
  public sealed partial class Channel : pb::IMessage<Channel>
  #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      , pb::IBufferMessage
  #endif
  {
    private static readonly pb::MessageParser<Channel> _parser = new pb::MessageParser<Channel>(() => new Channel());
    private pb::UnknownFieldSet _unknownFields;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pb::MessageParser<Channel> Parser { get { return _parser; } }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pbr::MessageDescriptor Descriptor {
      get { return global::Protocol.StructReflection.Descriptor.MessageTypes[0]; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    pbr::MessageDescriptor pb::IMessage.Descriptor {
      get { return Descriptor; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public Channel() {
      OnConstruction();
    }

    partial void OnConstruction();

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public Channel(Channel other) : this() {
      channelId_ = other.channelId_;
      maxPlayerCount_ = other.maxPlayerCount_;
      currentPlayerCount_ = other.currentPlayerCount_;
      _unknownFields = pb::UnknownFieldSet.Clone(other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public Channel Clone() {
      return new Channel(this);
    }

    /// <summary>Field number for the "channelId" field.</summary>
    public const int ChannelIdFieldNumber = 1;
    private int channelId_;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int ChannelId {
      get { return channelId_; }
      set {
        channelId_ = value;
      }
    }

    /// <summary>Field number for the "maxPlayerCount" field.</summary>
    public const int MaxPlayerCountFieldNumber = 2;
    private int maxPlayerCount_;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int MaxPlayerCount {
      get { return maxPlayerCount_; }
      set {
        maxPlayerCount_ = value;
      }
    }

    /// <summary>Field number for the "currentPlayerCount" field.</summary>
    public const int CurrentPlayerCountFieldNumber = 3;
    private int currentPlayerCount_;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int CurrentPlayerCount {
      get { return currentPlayerCount_; }
      set {
        currentPlayerCount_ = value;
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override bool Equals(object other) {
      return Equals(other as Channel);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public bool Equals(Channel other) {
      if (ReferenceEquals(other, null)) {
        return false;
      }
      if (ReferenceEquals(other, this)) {
        return true;
      }
      if (ChannelId != other.ChannelId) return false;
      if (MaxPlayerCount != other.MaxPlayerCount) return false;
      if (CurrentPlayerCount != other.CurrentPlayerCount) return false;
      return Equals(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override int GetHashCode() {
      int hash = 1;
      if (ChannelId != 0) hash ^= ChannelId.GetHashCode();
      if (MaxPlayerCount != 0) hash ^= MaxPlayerCount.GetHashCode();
      if (CurrentPlayerCount != 0) hash ^= CurrentPlayerCount.GetHashCode();
      if (_unknownFields != null) {
        hash ^= _unknownFields.GetHashCode();
      }
      return hash;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override string ToString() {
      return pb::JsonFormatter.ToDiagnosticString(this);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void WriteTo(pb::CodedOutputStream output) {
    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      output.WriteRawMessage(this);
    #else
      if (ChannelId != 0) {
        output.WriteRawTag(8);
        output.WriteInt32(ChannelId);
      }
      if (MaxPlayerCount != 0) {
        output.WriteRawTag(16);
        output.WriteInt32(MaxPlayerCount);
      }
      if (CurrentPlayerCount != 0) {
        output.WriteRawTag(24);
        output.WriteInt32(CurrentPlayerCount);
      }
      if (_unknownFields != null) {
        _unknownFields.WriteTo(output);
      }
    #endif
    }

    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    void pb::IBufferMessage.InternalWriteTo(ref pb::WriteContext output) {
      if (ChannelId != 0) {
        output.WriteRawTag(8);
        output.WriteInt32(ChannelId);
      }
      if (MaxPlayerCount != 0) {
        output.WriteRawTag(16);
        output.WriteInt32(MaxPlayerCount);
      }
      if (CurrentPlayerCount != 0) {
        output.WriteRawTag(24);
        output.WriteInt32(CurrentPlayerCount);
      }
      if (_unknownFields != null) {
        _unknownFields.WriteTo(ref output);
      }
    }
    #endif

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int CalculateSize() {
      int size = 0;
      if (ChannelId != 0) {
        size += 1 + pb::CodedOutputStream.ComputeInt32Size(ChannelId);
      }
      if (MaxPlayerCount != 0) {
        size += 1 + pb::CodedOutputStream.ComputeInt32Size(MaxPlayerCount);
      }
      if (CurrentPlayerCount != 0) {
        size += 1 + pb::CodedOutputStream.ComputeInt32Size(CurrentPlayerCount);
      }
      if (_unknownFields != null) {
        size += _unknownFields.CalculateSize();
      }
      return size;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void MergeFrom(Channel other) {
      if (other == null) {
        return;
      }
      if (other.ChannelId != 0) {
        ChannelId = other.ChannelId;
      }
      if (other.MaxPlayerCount != 0) {
        MaxPlayerCount = other.MaxPlayerCount;
      }
      if (other.CurrentPlayerCount != 0) {
        CurrentPlayerCount = other.CurrentPlayerCount;
      }
      _unknownFields = pb::UnknownFieldSet.MergeFrom(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void MergeFrom(pb::CodedInputStream input) {
    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      input.ReadRawMessage(this);
    #else
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
        switch(tag) {
          default:
            _unknownFields = pb::UnknownFieldSet.MergeFieldFrom(_unknownFields, input);
            break;
          case 8: {
            ChannelId = input.ReadInt32();
            break;
          }
          case 16: {
            MaxPlayerCount = input.ReadInt32();
            break;
          }
          case 24: {
            CurrentPlayerCount = input.ReadInt32();
            break;
          }
        }
      }
    #endif
    }

    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    void pb::IBufferMessage.InternalMergeFrom(ref pb::ParseContext input) {
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
        switch(tag) {
          default:
            _unknownFields = pb::UnknownFieldSet.MergeFieldFrom(_unknownFields, ref input);
            break;
          case 8: {
            ChannelId = input.ReadInt32();
            break;
          }
          case 16: {
            MaxPlayerCount = input.ReadInt32();
            break;
          }
          case 24: {
            CurrentPlayerCount = input.ReadInt32();
            break;
          }
        }
      }
    }
    #endif

  }

  public sealed partial class ChannelInfo : pb::IMessage<ChannelInfo>
  #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      , pb::IBufferMessage
  #endif
  {
    private static readonly pb::MessageParser<ChannelInfo> _parser = new pb::MessageParser<ChannelInfo>(() => new ChannelInfo());
    private pb::UnknownFieldSet _unknownFields;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pb::MessageParser<ChannelInfo> Parser { get { return _parser; } }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pbr::MessageDescriptor Descriptor {
      get { return global::Protocol.StructReflection.Descriptor.MessageTypes[1]; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    pbr::MessageDescriptor pb::IMessage.Descriptor {
      get { return Descriptor; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public ChannelInfo() {
      OnConstruction();
    }

    partial void OnConstruction();

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public ChannelInfo(ChannelInfo other) : this() {
      channelCount_ = other.channelCount_;
      channels_ = other.channels_.Clone();
      _unknownFields = pb::UnknownFieldSet.Clone(other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public ChannelInfo Clone() {
      return new ChannelInfo(this);
    }

    /// <summary>Field number for the "channelCount" field.</summary>
    public const int ChannelCountFieldNumber = 1;
    private int channelCount_;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int ChannelCount {
      get { return channelCount_; }
      set {
        channelCount_ = value;
      }
    }

    /// <summary>Field number for the "channels" field.</summary>
    public const int ChannelsFieldNumber = 2;
    private static readonly pb::FieldCodec<global::Protocol.Channel> _repeated_channels_codec
        = pb::FieldCodec.ForMessage(18, global::Protocol.Channel.Parser);
    private readonly pbc::RepeatedField<global::Protocol.Channel> channels_ = new pbc::RepeatedField<global::Protocol.Channel>();
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public pbc::RepeatedField<global::Protocol.Channel> Channels {
      get { return channels_; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override bool Equals(object other) {
      return Equals(other as ChannelInfo);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public bool Equals(ChannelInfo other) {
      if (ReferenceEquals(other, null)) {
        return false;
      }
      if (ReferenceEquals(other, this)) {
        return true;
      }
      if (ChannelCount != other.ChannelCount) return false;
      if(!channels_.Equals(other.channels_)) return false;
      return Equals(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override int GetHashCode() {
      int hash = 1;
      if (ChannelCount != 0) hash ^= ChannelCount.GetHashCode();
      hash ^= channels_.GetHashCode();
      if (_unknownFields != null) {
        hash ^= _unknownFields.GetHashCode();
      }
      return hash;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override string ToString() {
      return pb::JsonFormatter.ToDiagnosticString(this);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void WriteTo(pb::CodedOutputStream output) {
    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      output.WriteRawMessage(this);
    #else
      if (ChannelCount != 0) {
        output.WriteRawTag(8);
        output.WriteInt32(ChannelCount);
      }
      channels_.WriteTo(output, _repeated_channels_codec);
      if (_unknownFields != null) {
        _unknownFields.WriteTo(output);
      }
    #endif
    }

    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    void pb::IBufferMessage.InternalWriteTo(ref pb::WriteContext output) {
      if (ChannelCount != 0) {
        output.WriteRawTag(8);
        output.WriteInt32(ChannelCount);
      }
      channels_.WriteTo(ref output, _repeated_channels_codec);
      if (_unknownFields != null) {
        _unknownFields.WriteTo(ref output);
      }
    }
    #endif

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int CalculateSize() {
      int size = 0;
      if (ChannelCount != 0) {
        size += 1 + pb::CodedOutputStream.ComputeInt32Size(ChannelCount);
      }
      size += channels_.CalculateSize(_repeated_channels_codec);
      if (_unknownFields != null) {
        size += _unknownFields.CalculateSize();
      }
      return size;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void MergeFrom(ChannelInfo other) {
      if (other == null) {
        return;
      }
      if (other.ChannelCount != 0) {
        ChannelCount = other.ChannelCount;
      }
      channels_.Add(other.channels_);
      _unknownFields = pb::UnknownFieldSet.MergeFrom(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void MergeFrom(pb::CodedInputStream input) {
    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      input.ReadRawMessage(this);
    #else
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
        switch(tag) {
          default:
            _unknownFields = pb::UnknownFieldSet.MergeFieldFrom(_unknownFields, input);
            break;
          case 8: {
            ChannelCount = input.ReadInt32();
            break;
          }
          case 18: {
            channels_.AddEntriesFrom(input, _repeated_channels_codec);
            break;
          }
        }
      }
    #endif
    }

    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    void pb::IBufferMessage.InternalMergeFrom(ref pb::ParseContext input) {
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
        switch(tag) {
          default:
            _unknownFields = pb::UnknownFieldSet.MergeFieldFrom(_unknownFields, ref input);
            break;
          case 8: {
            ChannelCount = input.ReadInt32();
            break;
          }
          case 18: {
            channels_.AddEntriesFrom(ref input, _repeated_channels_codec);
            break;
          }
        }
      }
    }
    #endif

  }

  public sealed partial class Room : pb::IMessage<Room>
  #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      , pb::IBufferMessage
  #endif
  {
    private static readonly pb::MessageParser<Room> _parser = new pb::MessageParser<Room>(() => new Room());
    private pb::UnknownFieldSet _unknownFields;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pb::MessageParser<Room> Parser { get { return _parser; } }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pbr::MessageDescriptor Descriptor {
      get { return global::Protocol.StructReflection.Descriptor.MessageTypes[2]; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    pbr::MessageDescriptor pb::IMessage.Descriptor {
      get { return Descriptor; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public Room() {
      OnConstruction();
    }

    partial void OnConstruction();

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public Room(Room other) : this() {
      roomId_ = other.roomId_;
      roomName_ = other.roomName_;
      maxPlayerCount_ = other.maxPlayerCount_;
      currentPlayerCount_ = other.currentPlayerCount_;
      _unknownFields = pb::UnknownFieldSet.Clone(other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public Room Clone() {
      return new Room(this);
    }

    /// <summary>Field number for the "roomId" field.</summary>
    public const int RoomIdFieldNumber = 1;
    private int roomId_;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int RoomId {
      get { return roomId_; }
      set {
        roomId_ = value;
      }
    }

    /// <summary>Field number for the "roomName" field.</summary>
    public const int RoomNameFieldNumber = 2;
    private string roomName_ = "";
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public string RoomName {
      get { return roomName_; }
      set {
        roomName_ = pb::ProtoPreconditions.CheckNotNull(value, "value");
      }
    }

    /// <summary>Field number for the "maxPlayerCount" field.</summary>
    public const int MaxPlayerCountFieldNumber = 3;
    private int maxPlayerCount_;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int MaxPlayerCount {
      get { return maxPlayerCount_; }
      set {
        maxPlayerCount_ = value;
      }
    }

    /// <summary>Field number for the "currentPlayerCount" field.</summary>
    public const int CurrentPlayerCountFieldNumber = 4;
    private int currentPlayerCount_;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int CurrentPlayerCount {
      get { return currentPlayerCount_; }
      set {
        currentPlayerCount_ = value;
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override bool Equals(object other) {
      return Equals(other as Room);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public bool Equals(Room other) {
      if (ReferenceEquals(other, null)) {
        return false;
      }
      if (ReferenceEquals(other, this)) {
        return true;
      }
      if (RoomId != other.RoomId) return false;
      if (RoomName != other.RoomName) return false;
      if (MaxPlayerCount != other.MaxPlayerCount) return false;
      if (CurrentPlayerCount != other.CurrentPlayerCount) return false;
      return Equals(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override int GetHashCode() {
      int hash = 1;
      if (RoomId != 0) hash ^= RoomId.GetHashCode();
      if (RoomName.Length != 0) hash ^= RoomName.GetHashCode();
      if (MaxPlayerCount != 0) hash ^= MaxPlayerCount.GetHashCode();
      if (CurrentPlayerCount != 0) hash ^= CurrentPlayerCount.GetHashCode();
      if (_unknownFields != null) {
        hash ^= _unknownFields.GetHashCode();
      }
      return hash;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override string ToString() {
      return pb::JsonFormatter.ToDiagnosticString(this);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void WriteTo(pb::CodedOutputStream output) {
    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      output.WriteRawMessage(this);
    #else
      if (RoomId != 0) {
        output.WriteRawTag(8);
        output.WriteInt32(RoomId);
      }
      if (RoomName.Length != 0) {
        output.WriteRawTag(18);
        output.WriteString(RoomName);
      }
      if (MaxPlayerCount != 0) {
        output.WriteRawTag(24);
        output.WriteInt32(MaxPlayerCount);
      }
      if (CurrentPlayerCount != 0) {
        output.WriteRawTag(32);
        output.WriteInt32(CurrentPlayerCount);
      }
      if (_unknownFields != null) {
        _unknownFields.WriteTo(output);
      }
    #endif
    }

    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    void pb::IBufferMessage.InternalWriteTo(ref pb::WriteContext output) {
      if (RoomId != 0) {
        output.WriteRawTag(8);
        output.WriteInt32(RoomId);
      }
      if (RoomName.Length != 0) {
        output.WriteRawTag(18);
        output.WriteString(RoomName);
      }
      if (MaxPlayerCount != 0) {
        output.WriteRawTag(24);
        output.WriteInt32(MaxPlayerCount);
      }
      if (CurrentPlayerCount != 0) {
        output.WriteRawTag(32);
        output.WriteInt32(CurrentPlayerCount);
      }
      if (_unknownFields != null) {
        _unknownFields.WriteTo(ref output);
      }
    }
    #endif

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int CalculateSize() {
      int size = 0;
      if (RoomId != 0) {
        size += 1 + pb::CodedOutputStream.ComputeInt32Size(RoomId);
      }
      if (RoomName.Length != 0) {
        size += 1 + pb::CodedOutputStream.ComputeStringSize(RoomName);
      }
      if (MaxPlayerCount != 0) {
        size += 1 + pb::CodedOutputStream.ComputeInt32Size(MaxPlayerCount);
      }
      if (CurrentPlayerCount != 0) {
        size += 1 + pb::CodedOutputStream.ComputeInt32Size(CurrentPlayerCount);
      }
      if (_unknownFields != null) {
        size += _unknownFields.CalculateSize();
      }
      return size;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void MergeFrom(Room other) {
      if (other == null) {
        return;
      }
      if (other.RoomId != 0) {
        RoomId = other.RoomId;
      }
      if (other.RoomName.Length != 0) {
        RoomName = other.RoomName;
      }
      if (other.MaxPlayerCount != 0) {
        MaxPlayerCount = other.MaxPlayerCount;
      }
      if (other.CurrentPlayerCount != 0) {
        CurrentPlayerCount = other.CurrentPlayerCount;
      }
      _unknownFields = pb::UnknownFieldSet.MergeFrom(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void MergeFrom(pb::CodedInputStream input) {
    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      input.ReadRawMessage(this);
    #else
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
        switch(tag) {
          default:
            _unknownFields = pb::UnknownFieldSet.MergeFieldFrom(_unknownFields, input);
            break;
          case 8: {
            RoomId = input.ReadInt32();
            break;
          }
          case 18: {
            RoomName = input.ReadString();
            break;
          }
          case 24: {
            MaxPlayerCount = input.ReadInt32();
            break;
          }
          case 32: {
            CurrentPlayerCount = input.ReadInt32();
            break;
          }
        }
      }
    #endif
    }

    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    void pb::IBufferMessage.InternalMergeFrom(ref pb::ParseContext input) {
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
        switch(tag) {
          default:
            _unknownFields = pb::UnknownFieldSet.MergeFieldFrom(_unknownFields, ref input);
            break;
          case 8: {
            RoomId = input.ReadInt32();
            break;
          }
          case 18: {
            RoomName = input.ReadString();
            break;
          }
          case 24: {
            MaxPlayerCount = input.ReadInt32();
            break;
          }
          case 32: {
            CurrentPlayerCount = input.ReadInt32();
            break;
          }
        }
      }
    }
    #endif

  }

  public sealed partial class LobbyInfo : pb::IMessage<LobbyInfo>
  #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      , pb::IBufferMessage
  #endif
  {
    private static readonly pb::MessageParser<LobbyInfo> _parser = new pb::MessageParser<LobbyInfo>(() => new LobbyInfo());
    private pb::UnknownFieldSet _unknownFields;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pb::MessageParser<LobbyInfo> Parser { get { return _parser; } }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pbr::MessageDescriptor Descriptor {
      get { return global::Protocol.StructReflection.Descriptor.MessageTypes[3]; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    pbr::MessageDescriptor pb::IMessage.Descriptor {
      get { return Descriptor; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public LobbyInfo() {
      OnConstruction();
    }

    partial void OnConstruction();

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public LobbyInfo(LobbyInfo other) : this() {
      roomCount_ = other.roomCount_;
      rooms_ = other.rooms_.Clone();
      _unknownFields = pb::UnknownFieldSet.Clone(other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public LobbyInfo Clone() {
      return new LobbyInfo(this);
    }

    /// <summary>Field number for the "roomCount" field.</summary>
    public const int RoomCountFieldNumber = 1;
    private int roomCount_;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int RoomCount {
      get { return roomCount_; }
      set {
        roomCount_ = value;
      }
    }

    /// <summary>Field number for the "rooms" field.</summary>
    public const int RoomsFieldNumber = 2;
    private static readonly pb::FieldCodec<global::Protocol.Room> _repeated_rooms_codec
        = pb::FieldCodec.ForMessage(18, global::Protocol.Room.Parser);
    private readonly pbc::RepeatedField<global::Protocol.Room> rooms_ = new pbc::RepeatedField<global::Protocol.Room>();
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public pbc::RepeatedField<global::Protocol.Room> Rooms {
      get { return rooms_; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override bool Equals(object other) {
      return Equals(other as LobbyInfo);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public bool Equals(LobbyInfo other) {
      if (ReferenceEquals(other, null)) {
        return false;
      }
      if (ReferenceEquals(other, this)) {
        return true;
      }
      if (RoomCount != other.RoomCount) return false;
      if(!rooms_.Equals(other.rooms_)) return false;
      return Equals(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override int GetHashCode() {
      int hash = 1;
      if (RoomCount != 0) hash ^= RoomCount.GetHashCode();
      hash ^= rooms_.GetHashCode();
      if (_unknownFields != null) {
        hash ^= _unknownFields.GetHashCode();
      }
      return hash;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override string ToString() {
      return pb::JsonFormatter.ToDiagnosticString(this);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void WriteTo(pb::CodedOutputStream output) {
    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      output.WriteRawMessage(this);
    #else
      if (RoomCount != 0) {
        output.WriteRawTag(8);
        output.WriteInt32(RoomCount);
      }
      rooms_.WriteTo(output, _repeated_rooms_codec);
      if (_unknownFields != null) {
        _unknownFields.WriteTo(output);
      }
    #endif
    }

    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    void pb::IBufferMessage.InternalWriteTo(ref pb::WriteContext output) {
      if (RoomCount != 0) {
        output.WriteRawTag(8);
        output.WriteInt32(RoomCount);
      }
      rooms_.WriteTo(ref output, _repeated_rooms_codec);
      if (_unknownFields != null) {
        _unknownFields.WriteTo(ref output);
      }
    }
    #endif

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int CalculateSize() {
      int size = 0;
      if (RoomCount != 0) {
        size += 1 + pb::CodedOutputStream.ComputeInt32Size(RoomCount);
      }
      size += rooms_.CalculateSize(_repeated_rooms_codec);
      if (_unknownFields != null) {
        size += _unknownFields.CalculateSize();
      }
      return size;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void MergeFrom(LobbyInfo other) {
      if (other == null) {
        return;
      }
      if (other.RoomCount != 0) {
        RoomCount = other.RoomCount;
      }
      rooms_.Add(other.rooms_);
      _unknownFields = pb::UnknownFieldSet.MergeFrom(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void MergeFrom(pb::CodedInputStream input) {
    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      input.ReadRawMessage(this);
    #else
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
        switch(tag) {
          default:
            _unknownFields = pb::UnknownFieldSet.MergeFieldFrom(_unknownFields, input);
            break;
          case 8: {
            RoomCount = input.ReadInt32();
            break;
          }
          case 18: {
            rooms_.AddEntriesFrom(input, _repeated_rooms_codec);
            break;
          }
        }
      }
    #endif
    }

    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    void pb::IBufferMessage.InternalMergeFrom(ref pb::ParseContext input) {
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
        switch(tag) {
          default:
            _unknownFields = pb::UnknownFieldSet.MergeFieldFrom(_unknownFields, ref input);
            break;
          case 8: {
            RoomCount = input.ReadInt32();
            break;
          }
          case 18: {
            rooms_.AddEntriesFrom(ref input, _repeated_rooms_codec);
            break;
          }
        }
      }
    }
    #endif

  }

  #endregion

}

#endregion Designer generated code
