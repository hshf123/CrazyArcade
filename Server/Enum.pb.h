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

enum PRoomState : int {
  WAITING = 0,
  GAMESTART = 1,
  PRoomState_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  PRoomState_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool PRoomState_IsValid(int value);
constexpr PRoomState PRoomState_MIN = WAITING;
constexpr PRoomState PRoomState_MAX = GAMESTART;
constexpr int PRoomState_ARRAYSIZE = PRoomState_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* PRoomState_descriptor();
template<typename T>
inline const std::string& PRoomState_Name(T enum_t_value) {
  static_assert(::std::is_same<T, PRoomState>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function PRoomState_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    PRoomState_descriptor(), enum_t_value);
}
inline bool PRoomState_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, PRoomState* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<PRoomState>(
    PRoomState_descriptor(), name, value);
}
enum PPlayerState : int {
  IDLE = 0,
  MOVING = 1,
  INTRAP = 2,
  OUTTRAP = 3,
  DEAD = 4,
  PPlayerState_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  PPlayerState_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool PPlayerState_IsValid(int value);
constexpr PPlayerState PPlayerState_MIN = IDLE;
constexpr PPlayerState PPlayerState_MAX = DEAD;
constexpr int PPlayerState_ARRAYSIZE = PPlayerState_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* PPlayerState_descriptor();
template<typename T>
inline const std::string& PPlayerState_Name(T enum_t_value) {
  static_assert(::std::is_same<T, PPlayerState>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function PPlayerState_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    PPlayerState_descriptor(), enum_t_value);
}
inline bool PPlayerState_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, PPlayerState* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<PPlayerState>(
    PPlayerState_descriptor(), name, value);
}
enum PMoveDir : int {
  NONE = 0,
  UP = 1,
  RIGHT = 2,
  DOWN = 3,
  LEFT = 4,
  PMoveDir_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  PMoveDir_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool PMoveDir_IsValid(int value);
constexpr PMoveDir PMoveDir_MIN = NONE;
constexpr PMoveDir PMoveDir_MAX = LEFT;
constexpr int PMoveDir_ARRAYSIZE = PMoveDir_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* PMoveDir_descriptor();
template<typename T>
inline const std::string& PMoveDir_Name(T enum_t_value) {
  static_assert(::std::is_same<T, PMoveDir>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function PMoveDir_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    PMoveDir_descriptor(), enum_t_value);
}
inline bool PMoveDir_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, PMoveDir* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<PMoveDir>(
    PMoveDir_descriptor(), name, value);
}
enum PItemType : int {
  INCBOMBCOUNT = 0,
  INCBOMBRANGE = 1,
  MAXBOMBRANGE = 2,
  INCSPEED = 3,
  PItemType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  PItemType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool PItemType_IsValid(int value);
constexpr PItemType PItemType_MIN = INCBOMBCOUNT;
constexpr PItemType PItemType_MAX = INCSPEED;
constexpr int PItemType_ARRAYSIZE = PItemType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* PItemType_descriptor();
template<typename T>
inline const std::string& PItemType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, PItemType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function PItemType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    PItemType_descriptor(), enum_t_value);
}
inline bool PItemType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, PItemType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<PItemType>(
    PItemType_descriptor(), name, value);
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

template <> struct is_proto_enum< ::Protocol::PRoomState> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::PRoomState>() {
  return ::Protocol::PRoomState_descriptor();
}
template <> struct is_proto_enum< ::Protocol::PPlayerState> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::PPlayerState>() {
  return ::Protocol::PPlayerState_descriptor();
}
template <> struct is_proto_enum< ::Protocol::PMoveDir> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::PMoveDir>() {
  return ::Protocol::PMoveDir_descriptor();
}
template <> struct is_proto_enum< ::Protocol::PItemType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::PItemType>() {
  return ::Protocol::PItemType_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto
