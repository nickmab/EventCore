// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MathProto.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_MathProto_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_MathProto_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3011000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3011004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_MathProto_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_MathProto_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_MathProto_2eproto;
namespace mathproto {
class ArithmeticRequest;
class ArithmeticRequestDefaultTypeInternal;
extern ArithmeticRequestDefaultTypeInternal _ArithmeticRequest_default_instance_;
class ArithmeticResponse;
class ArithmeticResponseDefaultTypeInternal;
extern ArithmeticResponseDefaultTypeInternal _ArithmeticResponse_default_instance_;
class WrappedMessage;
class WrappedMessageDefaultTypeInternal;
extern WrappedMessageDefaultTypeInternal _WrappedMessage_default_instance_;
}  // namespace mathproto
PROTOBUF_NAMESPACE_OPEN
template<> ::mathproto::ArithmeticRequest* Arena::CreateMaybeMessage<::mathproto::ArithmeticRequest>(Arena*);
template<> ::mathproto::ArithmeticResponse* Arena::CreateMaybeMessage<::mathproto::ArithmeticResponse>(Arena*);
template<> ::mathproto::WrappedMessage* Arena::CreateMaybeMessage<::mathproto::WrappedMessage>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace mathproto {

enum ArithmeticOperator : int {
  PLUS = 0,
  MINUS = 1,
  TIMES = 2,
  DIVBY = 3,
  ArithmeticOperator_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  ArithmeticOperator_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool ArithmeticOperator_IsValid(int value);
constexpr ArithmeticOperator ArithmeticOperator_MIN = PLUS;
constexpr ArithmeticOperator ArithmeticOperator_MAX = DIVBY;
constexpr int ArithmeticOperator_ARRAYSIZE = ArithmeticOperator_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ArithmeticOperator_descriptor();
template<typename T>
inline const std::string& ArithmeticOperator_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ArithmeticOperator>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ArithmeticOperator_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    ArithmeticOperator_descriptor(), enum_t_value);
}
inline bool ArithmeticOperator_Parse(
    const std::string& name, ArithmeticOperator* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<ArithmeticOperator>(
    ArithmeticOperator_descriptor(), name, value);
}
// ===================================================================

class ArithmeticRequest :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mathproto.ArithmeticRequest) */ {
 public:
  ArithmeticRequest();
  virtual ~ArithmeticRequest();

  ArithmeticRequest(const ArithmeticRequest& from);
  ArithmeticRequest(ArithmeticRequest&& from) noexcept
    : ArithmeticRequest() {
    *this = ::std::move(from);
  }

  inline ArithmeticRequest& operator=(const ArithmeticRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline ArithmeticRequest& operator=(ArithmeticRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const ArithmeticRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ArithmeticRequest* internal_default_instance() {
    return reinterpret_cast<const ArithmeticRequest*>(
               &_ArithmeticRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ArithmeticRequest& a, ArithmeticRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(ArithmeticRequest* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline ArithmeticRequest* New() const final {
    return CreateMaybeMessage<ArithmeticRequest>(nullptr);
  }

  ArithmeticRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<ArithmeticRequest>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const ArithmeticRequest& from);
  void MergeFrom(const ArithmeticRequest& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ArithmeticRequest* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mathproto.ArithmeticRequest";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_MathProto_2eproto);
    return ::descriptor_table_MathProto_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kRequestIdFieldNumber = 1,
    kLhsFieldNumber = 2,
    kRhsFieldNumber = 4,
    kOpFieldNumber = 3,
  };
  // uint64 request_id = 1;
  void clear_request_id();
  ::PROTOBUF_NAMESPACE_ID::uint64 request_id() const;
  void set_request_id(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_request_id() const;
  void _internal_set_request_id(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // double lhs = 2;
  void clear_lhs();
  double lhs() const;
  void set_lhs(double value);
  private:
  double _internal_lhs() const;
  void _internal_set_lhs(double value);
  public:

  // double rhs = 4;
  void clear_rhs();
  double rhs() const;
  void set_rhs(double value);
  private:
  double _internal_rhs() const;
  void _internal_set_rhs(double value);
  public:

  // .mathproto.ArithmeticOperator op = 3;
  void clear_op();
  ::mathproto::ArithmeticOperator op() const;
  void set_op(::mathproto::ArithmeticOperator value);
  private:
  ::mathproto::ArithmeticOperator _internal_op() const;
  void _internal_set_op(::mathproto::ArithmeticOperator value);
  public:

  // @@protoc_insertion_point(class_scope:mathproto.ArithmeticRequest)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::uint64 request_id_;
  double lhs_;
  double rhs_;
  int op_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_MathProto_2eproto;
};
// -------------------------------------------------------------------

class ArithmeticResponse :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mathproto.ArithmeticResponse) */ {
 public:
  ArithmeticResponse();
  virtual ~ArithmeticResponse();

  ArithmeticResponse(const ArithmeticResponse& from);
  ArithmeticResponse(ArithmeticResponse&& from) noexcept
    : ArithmeticResponse() {
    *this = ::std::move(from);
  }

  inline ArithmeticResponse& operator=(const ArithmeticResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline ArithmeticResponse& operator=(ArithmeticResponse&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const ArithmeticResponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ArithmeticResponse* internal_default_instance() {
    return reinterpret_cast<const ArithmeticResponse*>(
               &_ArithmeticResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(ArithmeticResponse& a, ArithmeticResponse& b) {
    a.Swap(&b);
  }
  inline void Swap(ArithmeticResponse* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline ArithmeticResponse* New() const final {
    return CreateMaybeMessage<ArithmeticResponse>(nullptr);
  }

  ArithmeticResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<ArithmeticResponse>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const ArithmeticResponse& from);
  void MergeFrom(const ArithmeticResponse& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ArithmeticResponse* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mathproto.ArithmeticResponse";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_MathProto_2eproto);
    return ::descriptor_table_MathProto_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kRequestIdFieldNumber = 1,
    kResultFieldNumber = 2,
  };
  // uint64 request_id = 1;
  void clear_request_id();
  ::PROTOBUF_NAMESPACE_ID::uint64 request_id() const;
  void set_request_id(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_request_id() const;
  void _internal_set_request_id(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // double result = 2;
  void clear_result();
  double result() const;
  void set_result(double value);
  private:
  double _internal_result() const;
  void _internal_set_result(double value);
  public:

  // @@protoc_insertion_point(class_scope:mathproto.ArithmeticResponse)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::uint64 request_id_;
  double result_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_MathProto_2eproto;
};
// -------------------------------------------------------------------

class WrappedMessage :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mathproto.WrappedMessage) */ {
 public:
  WrappedMessage();
  virtual ~WrappedMessage();

  WrappedMessage(const WrappedMessage& from);
  WrappedMessage(WrappedMessage&& from) noexcept
    : WrappedMessage() {
    *this = ::std::move(from);
  }

  inline WrappedMessage& operator=(const WrappedMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline WrappedMessage& operator=(WrappedMessage&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const WrappedMessage& default_instance();

  enum MsgCase {
    kArithmeticRequest = 1,
    kArithmeticResponse = 2,
    MSG_NOT_SET = 0,
  };

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const WrappedMessage* internal_default_instance() {
    return reinterpret_cast<const WrappedMessage*>(
               &_WrappedMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(WrappedMessage& a, WrappedMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(WrappedMessage* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline WrappedMessage* New() const final {
    return CreateMaybeMessage<WrappedMessage>(nullptr);
  }

  WrappedMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<WrappedMessage>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const WrappedMessage& from);
  void MergeFrom(const WrappedMessage& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(WrappedMessage* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mathproto.WrappedMessage";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_MathProto_2eproto);
    return ::descriptor_table_MathProto_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kArithmeticRequestFieldNumber = 1,
    kArithmeticResponseFieldNumber = 2,
  };
  // .mathproto.ArithmeticRequest arithmetic_request = 1;
  bool has_arithmetic_request() const;
  private:
  bool _internal_has_arithmetic_request() const;
  public:
  void clear_arithmetic_request();
  const ::mathproto::ArithmeticRequest& arithmetic_request() const;
  ::mathproto::ArithmeticRequest* release_arithmetic_request();
  ::mathproto::ArithmeticRequest* mutable_arithmetic_request();
  void set_allocated_arithmetic_request(::mathproto::ArithmeticRequest* arithmetic_request);
  private:
  const ::mathproto::ArithmeticRequest& _internal_arithmetic_request() const;
  ::mathproto::ArithmeticRequest* _internal_mutable_arithmetic_request();
  public:

  // .mathproto.ArithmeticResponse arithmetic_response = 2;
  bool has_arithmetic_response() const;
  private:
  bool _internal_has_arithmetic_response() const;
  public:
  void clear_arithmetic_response();
  const ::mathproto::ArithmeticResponse& arithmetic_response() const;
  ::mathproto::ArithmeticResponse* release_arithmetic_response();
  ::mathproto::ArithmeticResponse* mutable_arithmetic_response();
  void set_allocated_arithmetic_response(::mathproto::ArithmeticResponse* arithmetic_response);
  private:
  const ::mathproto::ArithmeticResponse& _internal_arithmetic_response() const;
  ::mathproto::ArithmeticResponse* _internal_mutable_arithmetic_response();
  public:

  void clear_msg();
  MsgCase msg_case() const;
  // @@protoc_insertion_point(class_scope:mathproto.WrappedMessage)
 private:
  class _Internal;
  void set_has_arithmetic_request();
  void set_has_arithmetic_response();

  inline bool has_msg() const;
  inline void clear_has_msg();

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  union MsgUnion {
    MsgUnion() {}
    ::mathproto::ArithmeticRequest* arithmetic_request_;
    ::mathproto::ArithmeticResponse* arithmetic_response_;
  } msg_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::uint32 _oneof_case_[1];

  friend struct ::TableStruct_MathProto_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ArithmeticRequest

// uint64 request_id = 1;
inline void ArithmeticRequest::clear_request_id() {
  request_id_ = PROTOBUF_ULONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 ArithmeticRequest::_internal_request_id() const {
  return request_id_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 ArithmeticRequest::request_id() const {
  // @@protoc_insertion_point(field_get:mathproto.ArithmeticRequest.request_id)
  return _internal_request_id();
}
inline void ArithmeticRequest::_internal_set_request_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  request_id_ = value;
}
inline void ArithmeticRequest::set_request_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_request_id(value);
  // @@protoc_insertion_point(field_set:mathproto.ArithmeticRequest.request_id)
}

// double lhs = 2;
inline void ArithmeticRequest::clear_lhs() {
  lhs_ = 0;
}
inline double ArithmeticRequest::_internal_lhs() const {
  return lhs_;
}
inline double ArithmeticRequest::lhs() const {
  // @@protoc_insertion_point(field_get:mathproto.ArithmeticRequest.lhs)
  return _internal_lhs();
}
inline void ArithmeticRequest::_internal_set_lhs(double value) {
  
  lhs_ = value;
}
inline void ArithmeticRequest::set_lhs(double value) {
  _internal_set_lhs(value);
  // @@protoc_insertion_point(field_set:mathproto.ArithmeticRequest.lhs)
}

// .mathproto.ArithmeticOperator op = 3;
inline void ArithmeticRequest::clear_op() {
  op_ = 0;
}
inline ::mathproto::ArithmeticOperator ArithmeticRequest::_internal_op() const {
  return static_cast< ::mathproto::ArithmeticOperator >(op_);
}
inline ::mathproto::ArithmeticOperator ArithmeticRequest::op() const {
  // @@protoc_insertion_point(field_get:mathproto.ArithmeticRequest.op)
  return _internal_op();
}
inline void ArithmeticRequest::_internal_set_op(::mathproto::ArithmeticOperator value) {
  
  op_ = value;
}
inline void ArithmeticRequest::set_op(::mathproto::ArithmeticOperator value) {
  _internal_set_op(value);
  // @@protoc_insertion_point(field_set:mathproto.ArithmeticRequest.op)
}

// double rhs = 4;
inline void ArithmeticRequest::clear_rhs() {
  rhs_ = 0;
}
inline double ArithmeticRequest::_internal_rhs() const {
  return rhs_;
}
inline double ArithmeticRequest::rhs() const {
  // @@protoc_insertion_point(field_get:mathproto.ArithmeticRequest.rhs)
  return _internal_rhs();
}
inline void ArithmeticRequest::_internal_set_rhs(double value) {
  
  rhs_ = value;
}
inline void ArithmeticRequest::set_rhs(double value) {
  _internal_set_rhs(value);
  // @@protoc_insertion_point(field_set:mathproto.ArithmeticRequest.rhs)
}

// -------------------------------------------------------------------

// ArithmeticResponse

// uint64 request_id = 1;
inline void ArithmeticResponse::clear_request_id() {
  request_id_ = PROTOBUF_ULONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 ArithmeticResponse::_internal_request_id() const {
  return request_id_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 ArithmeticResponse::request_id() const {
  // @@protoc_insertion_point(field_get:mathproto.ArithmeticResponse.request_id)
  return _internal_request_id();
}
inline void ArithmeticResponse::_internal_set_request_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  request_id_ = value;
}
inline void ArithmeticResponse::set_request_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_request_id(value);
  // @@protoc_insertion_point(field_set:mathproto.ArithmeticResponse.request_id)
}

// double result = 2;
inline void ArithmeticResponse::clear_result() {
  result_ = 0;
}
inline double ArithmeticResponse::_internal_result() const {
  return result_;
}
inline double ArithmeticResponse::result() const {
  // @@protoc_insertion_point(field_get:mathproto.ArithmeticResponse.result)
  return _internal_result();
}
inline void ArithmeticResponse::_internal_set_result(double value) {
  
  result_ = value;
}
inline void ArithmeticResponse::set_result(double value) {
  _internal_set_result(value);
  // @@protoc_insertion_point(field_set:mathproto.ArithmeticResponse.result)
}

// -------------------------------------------------------------------

// WrappedMessage

// .mathproto.ArithmeticRequest arithmetic_request = 1;
inline bool WrappedMessage::_internal_has_arithmetic_request() const {
  return msg_case() == kArithmeticRequest;
}
inline bool WrappedMessage::has_arithmetic_request() const {
  return _internal_has_arithmetic_request();
}
inline void WrappedMessage::set_has_arithmetic_request() {
  _oneof_case_[0] = kArithmeticRequest;
}
inline void WrappedMessage::clear_arithmetic_request() {
  if (_internal_has_arithmetic_request()) {
    delete msg_.arithmetic_request_;
    clear_has_msg();
  }
}
inline ::mathproto::ArithmeticRequest* WrappedMessage::release_arithmetic_request() {
  // @@protoc_insertion_point(field_release:mathproto.WrappedMessage.arithmetic_request)
  if (_internal_has_arithmetic_request()) {
    clear_has_msg();
      ::mathproto::ArithmeticRequest* temp = msg_.arithmetic_request_;
    msg_.arithmetic_request_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::mathproto::ArithmeticRequest& WrappedMessage::_internal_arithmetic_request() const {
  return _internal_has_arithmetic_request()
      ? *msg_.arithmetic_request_
      : *reinterpret_cast< ::mathproto::ArithmeticRequest*>(&::mathproto::_ArithmeticRequest_default_instance_);
}
inline const ::mathproto::ArithmeticRequest& WrappedMessage::arithmetic_request() const {
  // @@protoc_insertion_point(field_get:mathproto.WrappedMessage.arithmetic_request)
  return _internal_arithmetic_request();
}
inline ::mathproto::ArithmeticRequest* WrappedMessage::_internal_mutable_arithmetic_request() {
  if (!_internal_has_arithmetic_request()) {
    clear_msg();
    set_has_arithmetic_request();
    msg_.arithmetic_request_ = CreateMaybeMessage< ::mathproto::ArithmeticRequest >(
        GetArenaNoVirtual());
  }
  return msg_.arithmetic_request_;
}
inline ::mathproto::ArithmeticRequest* WrappedMessage::mutable_arithmetic_request() {
  // @@protoc_insertion_point(field_mutable:mathproto.WrappedMessage.arithmetic_request)
  return _internal_mutable_arithmetic_request();
}

// .mathproto.ArithmeticResponse arithmetic_response = 2;
inline bool WrappedMessage::_internal_has_arithmetic_response() const {
  return msg_case() == kArithmeticResponse;
}
inline bool WrappedMessage::has_arithmetic_response() const {
  return _internal_has_arithmetic_response();
}
inline void WrappedMessage::set_has_arithmetic_response() {
  _oneof_case_[0] = kArithmeticResponse;
}
inline void WrappedMessage::clear_arithmetic_response() {
  if (_internal_has_arithmetic_response()) {
    delete msg_.arithmetic_response_;
    clear_has_msg();
  }
}
inline ::mathproto::ArithmeticResponse* WrappedMessage::release_arithmetic_response() {
  // @@protoc_insertion_point(field_release:mathproto.WrappedMessage.arithmetic_response)
  if (_internal_has_arithmetic_response()) {
    clear_has_msg();
      ::mathproto::ArithmeticResponse* temp = msg_.arithmetic_response_;
    msg_.arithmetic_response_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::mathproto::ArithmeticResponse& WrappedMessage::_internal_arithmetic_response() const {
  return _internal_has_arithmetic_response()
      ? *msg_.arithmetic_response_
      : *reinterpret_cast< ::mathproto::ArithmeticResponse*>(&::mathproto::_ArithmeticResponse_default_instance_);
}
inline const ::mathproto::ArithmeticResponse& WrappedMessage::arithmetic_response() const {
  // @@protoc_insertion_point(field_get:mathproto.WrappedMessage.arithmetic_response)
  return _internal_arithmetic_response();
}
inline ::mathproto::ArithmeticResponse* WrappedMessage::_internal_mutable_arithmetic_response() {
  if (!_internal_has_arithmetic_response()) {
    clear_msg();
    set_has_arithmetic_response();
    msg_.arithmetic_response_ = CreateMaybeMessage< ::mathproto::ArithmeticResponse >(
        GetArenaNoVirtual());
  }
  return msg_.arithmetic_response_;
}
inline ::mathproto::ArithmeticResponse* WrappedMessage::mutable_arithmetic_response() {
  // @@protoc_insertion_point(field_mutable:mathproto.WrappedMessage.arithmetic_response)
  return _internal_mutable_arithmetic_response();
}

inline bool WrappedMessage::has_msg() const {
  return msg_case() != MSG_NOT_SET;
}
inline void WrappedMessage::clear_has_msg() {
  _oneof_case_[0] = MSG_NOT_SET;
}
inline WrappedMessage::MsgCase WrappedMessage::msg_case() const {
  return WrappedMessage::MsgCase(_oneof_case_[0]);
}
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace mathproto

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::mathproto::ArithmeticOperator> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::mathproto::ArithmeticOperator>() {
  return ::mathproto::ArithmeticOperator_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_MathProto_2eproto
