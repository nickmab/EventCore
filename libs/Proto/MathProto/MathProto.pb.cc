// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MathProto.proto

#include "MathProto.pb.h"

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
extern PROTOBUF_INTERNAL_EXPORT_MathProto_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ArithmeticRequest_MathProto_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_MathProto_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ArithmeticResponse_MathProto_2eproto;
namespace mathproto {
class ArithmeticRequestDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ArithmeticRequest> _instance;
} _ArithmeticRequest_default_instance_;
class ArithmeticResponseDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ArithmeticResponse> _instance;
} _ArithmeticResponse_default_instance_;
class WrappedMessageDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<WrappedMessage> _instance;
  const ::mathproto::ArithmeticRequest* arithmetic_request_;
  const ::mathproto::ArithmeticResponse* arithmetic_response_;
} _WrappedMessage_default_instance_;
}  // namespace mathproto
static void InitDefaultsscc_info_ArithmeticRequest_MathProto_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::mathproto::_ArithmeticRequest_default_instance_;
    new (ptr) ::mathproto::ArithmeticRequest();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::mathproto::ArithmeticRequest::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ArithmeticRequest_MathProto_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_ArithmeticRequest_MathProto_2eproto}, {}};

static void InitDefaultsscc_info_ArithmeticResponse_MathProto_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::mathproto::_ArithmeticResponse_default_instance_;
    new (ptr) ::mathproto::ArithmeticResponse();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::mathproto::ArithmeticResponse::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ArithmeticResponse_MathProto_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_ArithmeticResponse_MathProto_2eproto}, {}};

static void InitDefaultsscc_info_WrappedMessage_MathProto_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::mathproto::_WrappedMessage_default_instance_;
    new (ptr) ::mathproto::WrappedMessage();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::mathproto::WrappedMessage::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<2> scc_info_WrappedMessage_MathProto_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 2, 0, InitDefaultsscc_info_WrappedMessage_MathProto_2eproto}, {
      &scc_info_ArithmeticRequest_MathProto_2eproto.base,
      &scc_info_ArithmeticResponse_MathProto_2eproto.base,}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_MathProto_2eproto[3];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_MathProto_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_MathProto_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_MathProto_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::mathproto::ArithmeticRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::mathproto::ArithmeticRequest, request_id_),
  PROTOBUF_FIELD_OFFSET(::mathproto::ArithmeticRequest, lhs_),
  PROTOBUF_FIELD_OFFSET(::mathproto::ArithmeticRequest, op_),
  PROTOBUF_FIELD_OFFSET(::mathproto::ArithmeticRequest, rhs_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::mathproto::ArithmeticResponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::mathproto::ArithmeticResponse, request_id_),
  PROTOBUF_FIELD_OFFSET(::mathproto::ArithmeticResponse, result_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::mathproto::WrappedMessage, _internal_metadata_),
  ~0u,  // no _extensions_
  PROTOBUF_FIELD_OFFSET(::mathproto::WrappedMessage, _oneof_case_[0]),
  ~0u,  // no _weak_field_map_
  offsetof(::mathproto::WrappedMessageDefaultTypeInternal, arithmetic_request_),
  offsetof(::mathproto::WrappedMessageDefaultTypeInternal, arithmetic_response_),
  PROTOBUF_FIELD_OFFSET(::mathproto::WrappedMessage, msg_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::mathproto::ArithmeticRequest)},
  { 9, -1, sizeof(::mathproto::ArithmeticResponse)},
  { 16, -1, sizeof(::mathproto::WrappedMessage)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::mathproto::_ArithmeticRequest_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::mathproto::_ArithmeticResponse_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::mathproto::_WrappedMessage_default_instance_),
};

const char descriptor_table_protodef_MathProto_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\017MathProto.proto\022\tmathproto\"l\n\021Arithmet"
  "icRequest\022\022\n\nrequest_id\030\001 \001(\004\022\013\n\003lhs\030\002 \001"
  "(\001\022)\n\002op\030\003 \001(\0162\035.mathproto.ArithmeticOpe"
  "rator\022\013\n\003rhs\030\004 \001(\001\"8\n\022ArithmeticResponse"
  "\022\022\n\nrequest_id\030\001 \001(\004\022\016\n\006result\030\002 \001(\001\"\221\001\n"
  "\016WrappedMessage\022:\n\022arithmetic_request\030\001 "
  "\001(\0132\034.mathproto.ArithmeticRequestH\000\022<\n\023a"
  "rithmetic_response\030\002 \001(\0132\035.mathproto.Ari"
  "thmeticResponseH\000B\005\n\003msg*\?\n\022ArithmeticOp"
  "erator\022\010\n\004PLUS\020\000\022\t\n\005MINUS\020\001\022\t\n\005TIMES\020\002\022\t"
  "\n\005DIVBY\020\003b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_MathProto_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_MathProto_2eproto_sccs[3] = {
  &scc_info_ArithmeticRequest_MathProto_2eproto.base,
  &scc_info_ArithmeticResponse_MathProto_2eproto.base,
  &scc_info_WrappedMessage_MathProto_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_MathProto_2eproto_once;
static bool descriptor_table_MathProto_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_MathProto_2eproto = {
  &descriptor_table_MathProto_2eproto_initialized, descriptor_table_protodef_MathProto_2eproto, "MathProto.proto", 417,
  &descriptor_table_MathProto_2eproto_once, descriptor_table_MathProto_2eproto_sccs, descriptor_table_MathProto_2eproto_deps, 3, 0,
  schemas, file_default_instances, TableStruct_MathProto_2eproto::offsets,
  file_level_metadata_MathProto_2eproto, 3, file_level_enum_descriptors_MathProto_2eproto, file_level_service_descriptors_MathProto_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_MathProto_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_MathProto_2eproto), true);
namespace mathproto {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ArithmeticOperator_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_MathProto_2eproto);
  return file_level_enum_descriptors_MathProto_2eproto[0];
}
bool ArithmeticOperator_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}


// ===================================================================

void ArithmeticRequest::InitAsDefaultInstance() {
}
class ArithmeticRequest::_Internal {
 public:
};

ArithmeticRequest::ArithmeticRequest()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:mathproto.ArithmeticRequest)
}
ArithmeticRequest::ArithmeticRequest(const ArithmeticRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&request_id_, &from.request_id_,
    static_cast<size_t>(reinterpret_cast<char*>(&op_) -
    reinterpret_cast<char*>(&request_id_)) + sizeof(op_));
  // @@protoc_insertion_point(copy_constructor:mathproto.ArithmeticRequest)
}

void ArithmeticRequest::SharedCtor() {
  ::memset(&request_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&op_) -
      reinterpret_cast<char*>(&request_id_)) + sizeof(op_));
}

ArithmeticRequest::~ArithmeticRequest() {
  // @@protoc_insertion_point(destructor:mathproto.ArithmeticRequest)
  SharedDtor();
}

void ArithmeticRequest::SharedDtor() {
}

void ArithmeticRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ArithmeticRequest& ArithmeticRequest::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ArithmeticRequest_MathProto_2eproto.base);
  return *internal_default_instance();
}


void ArithmeticRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:mathproto.ArithmeticRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&request_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&op_) -
      reinterpret_cast<char*>(&request_id_)) + sizeof(op_));
  _internal_metadata_.Clear();
}

const char* ArithmeticRequest::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // uint64 request_id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          request_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // double lhs = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 17)) {
          lhs_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      // .mathproto.ArithmeticOperator op = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
          _internal_set_op(static_cast<::mathproto::ArithmeticOperator>(val));
        } else goto handle_unusual;
        continue;
      // double rhs = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 33)) {
          rhs_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* ArithmeticRequest::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mathproto.ArithmeticRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 request_id = 1;
  if (this->request_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(1, this->_internal_request_id(), target);
  }

  // double lhs = 2;
  if (!(this->lhs() <= 0 && this->lhs() >= 0)) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(2, this->_internal_lhs(), target);
  }

  // .mathproto.ArithmeticOperator op = 3;
  if (this->op() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      3, this->_internal_op(), target);
  }

  // double rhs = 4;
  if (!(this->rhs() <= 0 && this->rhs() >= 0)) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(4, this->_internal_rhs(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mathproto.ArithmeticRequest)
  return target;
}

size_t ArithmeticRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mathproto.ArithmeticRequest)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // uint64 request_id = 1;
  if (this->request_id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
        this->_internal_request_id());
  }

  // double lhs = 2;
  if (!(this->lhs() <= 0 && this->lhs() >= 0)) {
    total_size += 1 + 8;
  }

  // double rhs = 4;
  if (!(this->rhs() <= 0 && this->rhs() >= 0)) {
    total_size += 1 + 8;
  }

  // .mathproto.ArithmeticOperator op = 3;
  if (this->op() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_op());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ArithmeticRequest::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:mathproto.ArithmeticRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const ArithmeticRequest* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<ArithmeticRequest>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:mathproto.ArithmeticRequest)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:mathproto.ArithmeticRequest)
    MergeFrom(*source);
  }
}

void ArithmeticRequest::MergeFrom(const ArithmeticRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:mathproto.ArithmeticRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.request_id() != 0) {
    _internal_set_request_id(from._internal_request_id());
  }
  if (!(from.lhs() <= 0 && from.lhs() >= 0)) {
    _internal_set_lhs(from._internal_lhs());
  }
  if (!(from.rhs() <= 0 && from.rhs() >= 0)) {
    _internal_set_rhs(from._internal_rhs());
  }
  if (from.op() != 0) {
    _internal_set_op(from._internal_op());
  }
}

void ArithmeticRequest::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:mathproto.ArithmeticRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ArithmeticRequest::CopyFrom(const ArithmeticRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mathproto.ArithmeticRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ArithmeticRequest::IsInitialized() const {
  return true;
}

void ArithmeticRequest::InternalSwap(ArithmeticRequest* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(request_id_, other->request_id_);
  swap(lhs_, other->lhs_);
  swap(rhs_, other->rhs_);
  swap(op_, other->op_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ArithmeticRequest::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void ArithmeticResponse::InitAsDefaultInstance() {
}
class ArithmeticResponse::_Internal {
 public:
};

ArithmeticResponse::ArithmeticResponse()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:mathproto.ArithmeticResponse)
}
ArithmeticResponse::ArithmeticResponse(const ArithmeticResponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&request_id_, &from.request_id_,
    static_cast<size_t>(reinterpret_cast<char*>(&result_) -
    reinterpret_cast<char*>(&request_id_)) + sizeof(result_));
  // @@protoc_insertion_point(copy_constructor:mathproto.ArithmeticResponse)
}

void ArithmeticResponse::SharedCtor() {
  ::memset(&request_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&result_) -
      reinterpret_cast<char*>(&request_id_)) + sizeof(result_));
}

ArithmeticResponse::~ArithmeticResponse() {
  // @@protoc_insertion_point(destructor:mathproto.ArithmeticResponse)
  SharedDtor();
}

void ArithmeticResponse::SharedDtor() {
}

void ArithmeticResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ArithmeticResponse& ArithmeticResponse::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ArithmeticResponse_MathProto_2eproto.base);
  return *internal_default_instance();
}


void ArithmeticResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:mathproto.ArithmeticResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&request_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&result_) -
      reinterpret_cast<char*>(&request_id_)) + sizeof(result_));
  _internal_metadata_.Clear();
}

const char* ArithmeticResponse::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // uint64 request_id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          request_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // double result = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 17)) {
          result_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* ArithmeticResponse::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mathproto.ArithmeticResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 request_id = 1;
  if (this->request_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(1, this->_internal_request_id(), target);
  }

  // double result = 2;
  if (!(this->result() <= 0 && this->result() >= 0)) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(2, this->_internal_result(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mathproto.ArithmeticResponse)
  return target;
}

size_t ArithmeticResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mathproto.ArithmeticResponse)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // uint64 request_id = 1;
  if (this->request_id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
        this->_internal_request_id());
  }

  // double result = 2;
  if (!(this->result() <= 0 && this->result() >= 0)) {
    total_size += 1 + 8;
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ArithmeticResponse::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:mathproto.ArithmeticResponse)
  GOOGLE_DCHECK_NE(&from, this);
  const ArithmeticResponse* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<ArithmeticResponse>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:mathproto.ArithmeticResponse)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:mathproto.ArithmeticResponse)
    MergeFrom(*source);
  }
}

void ArithmeticResponse::MergeFrom(const ArithmeticResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:mathproto.ArithmeticResponse)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.request_id() != 0) {
    _internal_set_request_id(from._internal_request_id());
  }
  if (!(from.result() <= 0 && from.result() >= 0)) {
    _internal_set_result(from._internal_result());
  }
}

void ArithmeticResponse::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:mathproto.ArithmeticResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ArithmeticResponse::CopyFrom(const ArithmeticResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mathproto.ArithmeticResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ArithmeticResponse::IsInitialized() const {
  return true;
}

void ArithmeticResponse::InternalSwap(ArithmeticResponse* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(request_id_, other->request_id_);
  swap(result_, other->result_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ArithmeticResponse::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void WrappedMessage::InitAsDefaultInstance() {
  ::mathproto::_WrappedMessage_default_instance_.arithmetic_request_ = const_cast< ::mathproto::ArithmeticRequest*>(
      ::mathproto::ArithmeticRequest::internal_default_instance());
  ::mathproto::_WrappedMessage_default_instance_.arithmetic_response_ = const_cast< ::mathproto::ArithmeticResponse*>(
      ::mathproto::ArithmeticResponse::internal_default_instance());
}
class WrappedMessage::_Internal {
 public:
  static const ::mathproto::ArithmeticRequest& arithmetic_request(const WrappedMessage* msg);
  static const ::mathproto::ArithmeticResponse& arithmetic_response(const WrappedMessage* msg);
};

const ::mathproto::ArithmeticRequest&
WrappedMessage::_Internal::arithmetic_request(const WrappedMessage* msg) {
  return *msg->msg_.arithmetic_request_;
}
const ::mathproto::ArithmeticResponse&
WrappedMessage::_Internal::arithmetic_response(const WrappedMessage* msg) {
  return *msg->msg_.arithmetic_response_;
}
void WrappedMessage::set_allocated_arithmetic_request(::mathproto::ArithmeticRequest* arithmetic_request) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  clear_msg();
  if (arithmetic_request) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      arithmetic_request = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, arithmetic_request, submessage_arena);
    }
    set_has_arithmetic_request();
    msg_.arithmetic_request_ = arithmetic_request;
  }
  // @@protoc_insertion_point(field_set_allocated:mathproto.WrappedMessage.arithmetic_request)
}
void WrappedMessage::set_allocated_arithmetic_response(::mathproto::ArithmeticResponse* arithmetic_response) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  clear_msg();
  if (arithmetic_response) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      arithmetic_response = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, arithmetic_response, submessage_arena);
    }
    set_has_arithmetic_response();
    msg_.arithmetic_response_ = arithmetic_response;
  }
  // @@protoc_insertion_point(field_set_allocated:mathproto.WrappedMessage.arithmetic_response)
}
WrappedMessage::WrappedMessage()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:mathproto.WrappedMessage)
}
WrappedMessage::WrappedMessage(const WrappedMessage& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  clear_has_msg();
  switch (from.msg_case()) {
    case kArithmeticRequest: {
      _internal_mutable_arithmetic_request()->::mathproto::ArithmeticRequest::MergeFrom(from._internal_arithmetic_request());
      break;
    }
    case kArithmeticResponse: {
      _internal_mutable_arithmetic_response()->::mathproto::ArithmeticResponse::MergeFrom(from._internal_arithmetic_response());
      break;
    }
    case MSG_NOT_SET: {
      break;
    }
  }
  // @@protoc_insertion_point(copy_constructor:mathproto.WrappedMessage)
}

void WrappedMessage::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_WrappedMessage_MathProto_2eproto.base);
  clear_has_msg();
}

WrappedMessage::~WrappedMessage() {
  // @@protoc_insertion_point(destructor:mathproto.WrappedMessage)
  SharedDtor();
}

void WrappedMessage::SharedDtor() {
  if (has_msg()) {
    clear_msg();
  }
}

void WrappedMessage::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const WrappedMessage& WrappedMessage::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_WrappedMessage_MathProto_2eproto.base);
  return *internal_default_instance();
}


void WrappedMessage::clear_msg() {
// @@protoc_insertion_point(one_of_clear_start:mathproto.WrappedMessage)
  switch (msg_case()) {
    case kArithmeticRequest: {
      delete msg_.arithmetic_request_;
      break;
    }
    case kArithmeticResponse: {
      delete msg_.arithmetic_response_;
      break;
    }
    case MSG_NOT_SET: {
      break;
    }
  }
  _oneof_case_[0] = MSG_NOT_SET;
}


void WrappedMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:mathproto.WrappedMessage)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  clear_msg();
  _internal_metadata_.Clear();
}

const char* WrappedMessage::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .mathproto.ArithmeticRequest arithmetic_request = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_arithmetic_request(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .mathproto.ArithmeticResponse arithmetic_response = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_arithmetic_response(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* WrappedMessage::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mathproto.WrappedMessage)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .mathproto.ArithmeticRequest arithmetic_request = 1;
  if (_internal_has_arithmetic_request()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        1, _Internal::arithmetic_request(this), target, stream);
  }

  // .mathproto.ArithmeticResponse arithmetic_response = 2;
  if (_internal_has_arithmetic_response()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::arithmetic_response(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mathproto.WrappedMessage)
  return target;
}

size_t WrappedMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mathproto.WrappedMessage)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  switch (msg_case()) {
    // .mathproto.ArithmeticRequest arithmetic_request = 1;
    case kArithmeticRequest: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *msg_.arithmetic_request_);
      break;
    }
    // .mathproto.ArithmeticResponse arithmetic_response = 2;
    case kArithmeticResponse: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *msg_.arithmetic_response_);
      break;
    }
    case MSG_NOT_SET: {
      break;
    }
  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void WrappedMessage::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:mathproto.WrappedMessage)
  GOOGLE_DCHECK_NE(&from, this);
  const WrappedMessage* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<WrappedMessage>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:mathproto.WrappedMessage)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:mathproto.WrappedMessage)
    MergeFrom(*source);
  }
}

void WrappedMessage::MergeFrom(const WrappedMessage& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:mathproto.WrappedMessage)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  switch (from.msg_case()) {
    case kArithmeticRequest: {
      _internal_mutable_arithmetic_request()->::mathproto::ArithmeticRequest::MergeFrom(from._internal_arithmetic_request());
      break;
    }
    case kArithmeticResponse: {
      _internal_mutable_arithmetic_response()->::mathproto::ArithmeticResponse::MergeFrom(from._internal_arithmetic_response());
      break;
    }
    case MSG_NOT_SET: {
      break;
    }
  }
}

void WrappedMessage::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:mathproto.WrappedMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void WrappedMessage::CopyFrom(const WrappedMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mathproto.WrappedMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool WrappedMessage::IsInitialized() const {
  return true;
}

void WrappedMessage::InternalSwap(WrappedMessage* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(msg_, other->msg_);
  swap(_oneof_case_[0], other->_oneof_case_[0]);
}

::PROTOBUF_NAMESPACE_ID::Metadata WrappedMessage::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace mathproto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::mathproto::ArithmeticRequest* Arena::CreateMaybeMessage< ::mathproto::ArithmeticRequest >(Arena* arena) {
  return Arena::CreateInternal< ::mathproto::ArithmeticRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::mathproto::ArithmeticResponse* Arena::CreateMaybeMessage< ::mathproto::ArithmeticResponse >(Arena* arena) {
  return Arena::CreateInternal< ::mathproto::ArithmeticResponse >(arena);
}
template<> PROTOBUF_NOINLINE ::mathproto::WrappedMessage* Arena::CreateMaybeMessage< ::mathproto::WrappedMessage >(Arena* arena) {
  return Arena::CreateInternal< ::mathproto::WrappedMessage >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
