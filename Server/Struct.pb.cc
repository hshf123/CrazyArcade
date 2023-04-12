// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Struct.proto

#include "Struct.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace Protocol {
PROTOBUF_CONSTEXPR Channel::Channel(
    ::_pbi::ConstantInitialized)
  : channelid_(0)
  , maxplayercount_(0)
  , currentplayercount_(0){}
struct ChannelDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ChannelDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~ChannelDefaultTypeInternal() {}
  union {
    Channel _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ChannelDefaultTypeInternal _Channel_default_instance_;
PROTOBUF_CONSTEXPR ChannelInfo::ChannelInfo(
    ::_pbi::ConstantInitialized)
  : channels_()
  , channelcount_(0){}
struct ChannelInfoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ChannelInfoDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~ChannelInfoDefaultTypeInternal() {}
  union {
    ChannelInfo _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ChannelInfoDefaultTypeInternal _ChannelInfo_default_instance_;
PROTOBUF_CONSTEXPR Room::Room(
    ::_pbi::ConstantInitialized)
  : roomname_(&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{})
  , roomid_(0)
  , maxplayercount_(0)
  , currentplayercount_(0){}
struct RoomDefaultTypeInternal {
  PROTOBUF_CONSTEXPR RoomDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~RoomDefaultTypeInternal() {}
  union {
    Room _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 RoomDefaultTypeInternal _Room_default_instance_;
PROTOBUF_CONSTEXPR RoomInfo::RoomInfo(
    ::_pbi::ConstantInitialized)
  : rooms_()
  , roomcount_(0){}
struct RoomInfoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR RoomInfoDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~RoomInfoDefaultTypeInternal() {}
  union {
    RoomInfo _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 RoomInfoDefaultTypeInternal _RoomInfo_default_instance_;
}  // namespace Protocol
static ::_pb::Metadata file_level_metadata_Struct_2eproto[4];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_Struct_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_Struct_2eproto = nullptr;

const uint32_t TableStruct_Struct_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::Channel, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Protocol::Channel, channelid_),
  PROTOBUF_FIELD_OFFSET(::Protocol::Channel, maxplayercount_),
  PROTOBUF_FIELD_OFFSET(::Protocol::Channel, currentplayercount_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::ChannelInfo, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Protocol::ChannelInfo, channelcount_),
  PROTOBUF_FIELD_OFFSET(::Protocol::ChannelInfo, channels_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::Room, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Protocol::Room, roomid_),
  PROTOBUF_FIELD_OFFSET(::Protocol::Room, roomname_),
  PROTOBUF_FIELD_OFFSET(::Protocol::Room, maxplayercount_),
  PROTOBUF_FIELD_OFFSET(::Protocol::Room, currentplayercount_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::RoomInfo, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Protocol::RoomInfo, roomcount_),
  PROTOBUF_FIELD_OFFSET(::Protocol::RoomInfo, rooms_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Protocol::Channel)},
  { 9, -1, -1, sizeof(::Protocol::ChannelInfo)},
  { 17, -1, -1, sizeof(::Protocol::Room)},
  { 27, -1, -1, sizeof(::Protocol::RoomInfo)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::Protocol::_Channel_default_instance_._instance,
  &::Protocol::_ChannelInfo_default_instance_._instance,
  &::Protocol::_Room_default_instance_._instance,
  &::Protocol::_RoomInfo_default_instance_._instance,
};

const char descriptor_table_protodef_Struct_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\014Struct.proto\022\010Protocol\032\nEnum.proto\"P\n\007"
  "Channel\022\021\n\tchannelId\030\001 \001(\005\022\026\n\016maxPlayerC"
  "ount\030\002 \001(\005\022\032\n\022currentPlayerCount\030\003 \001(\005\"H"
  "\n\013ChannelInfo\022\024\n\014channelCount\030\001 \001(\005\022#\n\010c"
  "hannels\030\002 \003(\0132\021.Protocol.Channel\"\\\n\004Room"
  "\022\016\n\006roomId\030\001 \001(\005\022\020\n\010roomName\030\002 \001(\t\022\026\n\016ma"
  "xPlayerCount\030\003 \001(\005\022\032\n\022currentPlayerCount"
  "\030\004 \001(\005\"<\n\010RoomInfo\022\021\n\troomCount\030\001 \001(\005\022\035\n"
  "\005rooms\030\002 \003(\0132\016.Protocol.Roomb\006proto3"
  ;
static const ::_pbi::DescriptorTable* const descriptor_table_Struct_2eproto_deps[1] = {
  &::descriptor_table_Enum_2eproto,
};
static ::_pbi::once_flag descriptor_table_Struct_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_Struct_2eproto = {
    false, false, 356, descriptor_table_protodef_Struct_2eproto,
    "Struct.proto",
    &descriptor_table_Struct_2eproto_once, descriptor_table_Struct_2eproto_deps, 1, 4,
    schemas, file_default_instances, TableStruct_Struct_2eproto::offsets,
    file_level_metadata_Struct_2eproto, file_level_enum_descriptors_Struct_2eproto,
    file_level_service_descriptors_Struct_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_Struct_2eproto_getter() {
  return &descriptor_table_Struct_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_Struct_2eproto(&descriptor_table_Struct_2eproto);
namespace Protocol {

// ===================================================================

class Channel::_Internal {
 public:
};

Channel::Channel(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  // @@protoc_insertion_point(arena_constructor:Protocol.Channel)
}
Channel::Channel(const Channel& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&channelid_, &from.channelid_,
    static_cast<size_t>(reinterpret_cast<char*>(&currentplayercount_) -
    reinterpret_cast<char*>(&channelid_)) + sizeof(currentplayercount_));
  // @@protoc_insertion_point(copy_constructor:Protocol.Channel)
}

inline void Channel::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&channelid_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&currentplayercount_) -
    reinterpret_cast<char*>(&channelid_)) + sizeof(currentplayercount_));
}

Channel::~Channel() {
  // @@protoc_insertion_point(destructor:Protocol.Channel)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Channel::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Channel::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Channel::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.Channel)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&channelid_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&currentplayercount_) -
      reinterpret_cast<char*>(&channelid_)) + sizeof(currentplayercount_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Channel::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 channelId = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          channelid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 maxPlayerCount = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          maxplayercount_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 currentPlayerCount = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          currentplayercount_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Channel::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.Channel)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 channelId = 1;
  if (this->_internal_channelid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_channelid(), target);
  }

  // int32 maxPlayerCount = 2;
  if (this->_internal_maxplayercount() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_maxplayercount(), target);
  }

  // int32 currentPlayerCount = 3;
  if (this->_internal_currentplayercount() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(3, this->_internal_currentplayercount(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.Channel)
  return target;
}

size_t Channel::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.Channel)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 channelId = 1;
  if (this->_internal_channelid() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_channelid());
  }

  // int32 maxPlayerCount = 2;
  if (this->_internal_maxplayercount() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_maxplayercount());
  }

  // int32 currentPlayerCount = 3;
  if (this->_internal_currentplayercount() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_currentplayercount());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Channel::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Channel::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Channel::GetClassData() const { return &_class_data_; }

void Channel::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Channel *>(to)->MergeFrom(
      static_cast<const Channel &>(from));
}


void Channel::MergeFrom(const Channel& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protocol.Channel)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_channelid() != 0) {
    _internal_set_channelid(from._internal_channelid());
  }
  if (from._internal_maxplayercount() != 0) {
    _internal_set_maxplayercount(from._internal_maxplayercount());
  }
  if (from._internal_currentplayercount() != 0) {
    _internal_set_currentplayercount(from._internal_currentplayercount());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Channel::CopyFrom(const Channel& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.Channel)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Channel::IsInitialized() const {
  return true;
}

void Channel::InternalSwap(Channel* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Channel, currentplayercount_)
      + sizeof(Channel::currentplayercount_)
      - PROTOBUF_FIELD_OFFSET(Channel, channelid_)>(
          reinterpret_cast<char*>(&channelid_),
          reinterpret_cast<char*>(&other->channelid_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Channel::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Struct_2eproto_getter, &descriptor_table_Struct_2eproto_once,
      file_level_metadata_Struct_2eproto[0]);
}

// ===================================================================

class ChannelInfo::_Internal {
 public:
};

ChannelInfo::ChannelInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  channels_(arena) {
  SharedCtor();
  // @@protoc_insertion_point(arena_constructor:Protocol.ChannelInfo)
}
ChannelInfo::ChannelInfo(const ChannelInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      channels_(from.channels_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  channelcount_ = from.channelcount_;
  // @@protoc_insertion_point(copy_constructor:Protocol.ChannelInfo)
}

inline void ChannelInfo::SharedCtor() {
channelcount_ = 0;
}

ChannelInfo::~ChannelInfo() {
  // @@protoc_insertion_point(destructor:Protocol.ChannelInfo)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void ChannelInfo::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void ChannelInfo::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void ChannelInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.ChannelInfo)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  channels_.Clear();
  channelcount_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ChannelInfo::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 channelCount = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          channelcount_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated .Protocol.Channel channels = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_channels(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* ChannelInfo::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.ChannelInfo)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 channelCount = 1;
  if (this->_internal_channelcount() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_channelcount(), target);
  }

  // repeated .Protocol.Channel channels = 2;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_channels_size()); i < n; i++) {
    const auto& repfield = this->_internal_channels(i);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessage(2, repfield, repfield.GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.ChannelInfo)
  return target;
}

size_t ChannelInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.ChannelInfo)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .Protocol.Channel channels = 2;
  total_size += 1UL * this->_internal_channels_size();
  for (const auto& msg : this->channels_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // int32 channelCount = 1;
  if (this->_internal_channelcount() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_channelcount());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData ChannelInfo::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    ChannelInfo::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*ChannelInfo::GetClassData() const { return &_class_data_; }

void ChannelInfo::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<ChannelInfo *>(to)->MergeFrom(
      static_cast<const ChannelInfo &>(from));
}


void ChannelInfo::MergeFrom(const ChannelInfo& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protocol.ChannelInfo)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  channels_.MergeFrom(from.channels_);
  if (from._internal_channelcount() != 0) {
    _internal_set_channelcount(from._internal_channelcount());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void ChannelInfo::CopyFrom(const ChannelInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.ChannelInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ChannelInfo::IsInitialized() const {
  return true;
}

void ChannelInfo::InternalSwap(ChannelInfo* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  channels_.InternalSwap(&other->channels_);
  swap(channelcount_, other->channelcount_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ChannelInfo::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Struct_2eproto_getter, &descriptor_table_Struct_2eproto_once,
      file_level_metadata_Struct_2eproto[1]);
}

// ===================================================================

class Room::_Internal {
 public:
};

Room::Room(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  // @@protoc_insertion_point(arena_constructor:Protocol.Room)
}
Room::Room(const Room& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  roomname_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    roomname_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_roomname().empty()) {
    roomname_.Set(from._internal_roomname(), 
      GetArenaForAllocation());
  }
  ::memcpy(&roomid_, &from.roomid_,
    static_cast<size_t>(reinterpret_cast<char*>(&currentplayercount_) -
    reinterpret_cast<char*>(&roomid_)) + sizeof(currentplayercount_));
  // @@protoc_insertion_point(copy_constructor:Protocol.Room)
}

inline void Room::SharedCtor() {
roomname_.InitDefault();
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  roomname_.Set("", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&roomid_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&currentplayercount_) -
    reinterpret_cast<char*>(&roomid_)) + sizeof(currentplayercount_));
}

Room::~Room() {
  // @@protoc_insertion_point(destructor:Protocol.Room)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Room::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  roomname_.Destroy();
}

void Room::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Room::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.Room)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  roomname_.ClearToEmpty();
  ::memset(&roomid_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&currentplayercount_) -
      reinterpret_cast<char*>(&roomid_)) + sizeof(currentplayercount_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Room::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 roomId = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          roomid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string roomName = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_roomname();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Protocol.Room.roomName"));
        } else
          goto handle_unusual;
        continue;
      // int32 maxPlayerCount = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          maxplayercount_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 currentPlayerCount = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          currentplayercount_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Room::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.Room)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 roomId = 1;
  if (this->_internal_roomid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_roomid(), target);
  }

  // string roomName = 2;
  if (!this->_internal_roomname().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_roomname().data(), static_cast<int>(this->_internal_roomname().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Protocol.Room.roomName");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_roomname(), target);
  }

  // int32 maxPlayerCount = 3;
  if (this->_internal_maxplayercount() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(3, this->_internal_maxplayercount(), target);
  }

  // int32 currentPlayerCount = 4;
  if (this->_internal_currentplayercount() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(4, this->_internal_currentplayercount(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.Room)
  return target;
}

size_t Room::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.Room)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string roomName = 2;
  if (!this->_internal_roomname().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_roomname());
  }

  // int32 roomId = 1;
  if (this->_internal_roomid() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_roomid());
  }

  // int32 maxPlayerCount = 3;
  if (this->_internal_maxplayercount() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_maxplayercount());
  }

  // int32 currentPlayerCount = 4;
  if (this->_internal_currentplayercount() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_currentplayercount());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Room::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Room::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Room::GetClassData() const { return &_class_data_; }

void Room::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Room *>(to)->MergeFrom(
      static_cast<const Room &>(from));
}


void Room::MergeFrom(const Room& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protocol.Room)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_roomname().empty()) {
    _internal_set_roomname(from._internal_roomname());
  }
  if (from._internal_roomid() != 0) {
    _internal_set_roomid(from._internal_roomid());
  }
  if (from._internal_maxplayercount() != 0) {
    _internal_set_maxplayercount(from._internal_maxplayercount());
  }
  if (from._internal_currentplayercount() != 0) {
    _internal_set_currentplayercount(from._internal_currentplayercount());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Room::CopyFrom(const Room& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.Room)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Room::IsInitialized() const {
  return true;
}

void Room::InternalSwap(Room* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &roomname_, lhs_arena,
      &other->roomname_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Room, currentplayercount_)
      + sizeof(Room::currentplayercount_)
      - PROTOBUF_FIELD_OFFSET(Room, roomid_)>(
          reinterpret_cast<char*>(&roomid_),
          reinterpret_cast<char*>(&other->roomid_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Room::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Struct_2eproto_getter, &descriptor_table_Struct_2eproto_once,
      file_level_metadata_Struct_2eproto[2]);
}

// ===================================================================

class RoomInfo::_Internal {
 public:
};

RoomInfo::RoomInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  rooms_(arena) {
  SharedCtor();
  // @@protoc_insertion_point(arena_constructor:Protocol.RoomInfo)
}
RoomInfo::RoomInfo(const RoomInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      rooms_(from.rooms_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  roomcount_ = from.roomcount_;
  // @@protoc_insertion_point(copy_constructor:Protocol.RoomInfo)
}

inline void RoomInfo::SharedCtor() {
roomcount_ = 0;
}

RoomInfo::~RoomInfo() {
  // @@protoc_insertion_point(destructor:Protocol.RoomInfo)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void RoomInfo::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void RoomInfo::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void RoomInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.RoomInfo)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  rooms_.Clear();
  roomcount_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* RoomInfo::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 roomCount = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          roomcount_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated .Protocol.Room rooms = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_rooms(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* RoomInfo::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.RoomInfo)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 roomCount = 1;
  if (this->_internal_roomcount() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_roomcount(), target);
  }

  // repeated .Protocol.Room rooms = 2;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_rooms_size()); i < n; i++) {
    const auto& repfield = this->_internal_rooms(i);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessage(2, repfield, repfield.GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.RoomInfo)
  return target;
}

size_t RoomInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.RoomInfo)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .Protocol.Room rooms = 2;
  total_size += 1UL * this->_internal_rooms_size();
  for (const auto& msg : this->rooms_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // int32 roomCount = 1;
  if (this->_internal_roomcount() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_roomcount());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData RoomInfo::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    RoomInfo::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*RoomInfo::GetClassData() const { return &_class_data_; }

void RoomInfo::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<RoomInfo *>(to)->MergeFrom(
      static_cast<const RoomInfo &>(from));
}


void RoomInfo::MergeFrom(const RoomInfo& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protocol.RoomInfo)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  rooms_.MergeFrom(from.rooms_);
  if (from._internal_roomcount() != 0) {
    _internal_set_roomcount(from._internal_roomcount());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void RoomInfo::CopyFrom(const RoomInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.RoomInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RoomInfo::IsInitialized() const {
  return true;
}

void RoomInfo::InternalSwap(RoomInfo* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  rooms_.InternalSwap(&other->rooms_);
  swap(roomcount_, other->roomcount_);
}

::PROTOBUF_NAMESPACE_ID::Metadata RoomInfo::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Struct_2eproto_getter, &descriptor_table_Struct_2eproto_once,
      file_level_metadata_Struct_2eproto[3]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Protocol::Channel*
Arena::CreateMaybeMessage< ::Protocol::Channel >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::Channel >(arena);
}
template<> PROTOBUF_NOINLINE ::Protocol::ChannelInfo*
Arena::CreateMaybeMessage< ::Protocol::ChannelInfo >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::ChannelInfo >(arena);
}
template<> PROTOBUF_NOINLINE ::Protocol::Room*
Arena::CreateMaybeMessage< ::Protocol::Room >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::Room >(arena);
}
template<> PROTOBUF_NOINLINE ::Protocol::RoomInfo*
Arena::CreateMaybeMessage< ::Protocol::RoomInfo >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::RoomInfo >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
