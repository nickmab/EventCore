// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DemoProto.proto

#include "DemoProto.pb.h"

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
namespace demoproto {
class ExampleDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Example> _instance;
} _Example_default_instance_;
}  // namespace demoproto
static void InitDefaultsscc_info_Example_DemoProto_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::demoproto::_Example_default_instance_;
    new (ptr) ::demoproto::Example();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::demoproto::Example::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Example_DemoProto_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_Example_DemoProto_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_DemoProto_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_DemoProto_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_DemoProto_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_DemoProto_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::demoproto::Example, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::demoproto::Example, anumber_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::demoproto::Example)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::demoproto::_Example_default_instance_),
};

const char descriptor_table_protodef_DemoProto_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\017DemoProto.proto\022\tdemoproto\"\032\n\007Example\022"
  "\017\n\007aNumber\030\001 \001(\005b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_DemoProto_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_DemoProto_2eproto_sccs[1] = {
  &scc_info_Example_DemoProto_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_DemoProto_2eproto_once;
static bool descriptor_table_DemoProto_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_DemoProto_2eproto = {
  &descriptor_table_DemoProto_2eproto_initialized, descriptor_table_protodef_DemoProto_2eproto, "DemoProto.proto", 64,
  &descriptor_table_DemoProto_2eproto_once, descriptor_table_DemoProto_2eproto_sccs, descriptor_table_DemoProto_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_DemoProto_2eproto::offsets,
  file_level_metadata_DemoProto_2eproto, 1, file_level_enum_descriptors_DemoProto_2eproto, file_level_service_descriptors_DemoProto_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_DemoProto_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_DemoProto_2eproto), true);
namespace demoproto {

// ===================================================================

void Example::InitAsDefaultInstance() {
}
class Example::_Internal {
 public:
};

Example::Example()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:demoproto.Example)
}
Example::Example(const Example& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  anumber_ = from.anumber_;
  // @@protoc_insertion_point(copy_constructor:demoproto.Example)
}

void Example::SharedCtor() {
  anumber_ = 0;
}

Example::~Example() {
  // @@protoc_insertion_point(destructor:demoproto.Example)
  SharedDtor();
}

void Example::SharedDtor() {
}

void Example::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Example& Example::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Example_DemoProto_2eproto.base);
  return *internal_default_instance();
}


void Example::Clear() {
// @@protoc_insertion_point(message_clear_start:demoproto.Example)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  anumber_ = 0;
  _internal_metadata_.Clear();
}

const char* Example::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int32 aNumber = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          anumber_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
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

::PROTOBUF_NAMESPACE_ID::uint8* Example::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:demoproto.Example)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 aNumber = 1;
  if (this->anumber() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_anumber(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:demoproto.Example)
  return target;
}

size_t Example::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:demoproto.Example)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 aNumber = 1;
  if (this->anumber() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_anumber());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Example::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:demoproto.Example)
  GOOGLE_DCHECK_NE(&from, this);
  const Example* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Example>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:demoproto.Example)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:demoproto.Example)
    MergeFrom(*source);
  }
}

void Example::MergeFrom(const Example& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:demoproto.Example)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.anumber() != 0) {
    _internal_set_anumber(from._internal_anumber());
  }
}

void Example::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:demoproto.Example)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Example::CopyFrom(const Example& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:demoproto.Example)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Example::IsInitialized() const {
  return true;
}

void Example::InternalSwap(Example* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(anumber_, other->anumber_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Example::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace demoproto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::demoproto::Example* Arena::CreateMaybeMessage< ::demoproto::Example >(Arena* arena) {
  return Arena::CreateInternal< ::demoproto::Example >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>