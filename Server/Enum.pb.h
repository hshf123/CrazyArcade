// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Enum.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3020000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3020001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Enum_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Enum_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Enum_2eproto;
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

enum RoomState : int {
  WAITING = 0,
  GAMESTART = 1,
  RoomState_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  RoomState_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool RoomState_IsValid(int value);
constexpr RoomState RoomState_MIN = WAITING;
constexpr RoomState RoomState_MAX = GAMESTART;
constexpr int RoomState_ARRAYSIZE = RoomState_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* RoomState_descriptor();
template<typename T>
inline const std::string& RoomState_Name(T enum_t_value) {
  static_assert(::std::is_same<T, RoomState>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function RoomState_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    RoomState_descriptor(), enum_t_value);
}
inline bool RoomState_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, RoomState* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<RoomState>(
    RoomState_descriptor(), name, value);
}
enum PlayerState : int {
  IDLE = 0,
  MOVING = 1,
  INTRAP = 2,
  OUTTRAP = 3,
  DEAD = 4,
  PlayerState_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  PlayerState_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool PlayerState_IsValid(int value);
constexpr PlayerState PlayerState_MIN = IDLE;
constexpr PlayerState PlayerState_MAX = DEAD;
constexpr int PlayerState_ARRAYSIZE = PlayerState_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* PlayerState_descriptor();
template<typename T>
inline const std::string& PlayerState_Name(T enum_t_value) {
  static_assert(::std::is_same<T, PlayerState>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function PlayerState_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    PlayerState_descriptor(), enum_t_value);
}
inline bool PlayerState_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, PlayerState* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<PlayerState>(
    PlayerState_descriptor(), name, value);
}
enum MoveDir : int {
  NONE = 0,
  UP = 1,
  RIGHT = 2,
  DOWN = 3,
  LEFT = 4,
  MoveDir_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  MoveDir_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool MoveDir_IsValid(int value);
constexpr MoveDir MoveDir_MIN = NONE;
constexpr MoveDir MoveDir_MAX = LEFT;
constexpr int MoveDir_ARRAYSIZE = MoveDir_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MoveDir_descriptor();
template<typename T>
inline const std::string& MoveDir_Name(T enum_t_value) {
  static_assert(::std::is_same<T, MoveDir>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function MoveDir_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    MoveDir_descriptor(), enum_t_value);
}
inline bool MoveDir_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, MoveDir* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<MoveDir>(
    MoveDir_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::Protocol::RoomState> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::RoomState>() {
  return ::Protocol::RoomState_descriptor();
}
template <> struct is_proto_enum< ::Protocol::PlayerState> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::PlayerState>() {
  return ::Protocol::PlayerState_descriptor();
}
template <> struct is_proto_enum< ::Protocol::MoveDir> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::MoveDir>() {
  return ::Protocol::MoveDir_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto
