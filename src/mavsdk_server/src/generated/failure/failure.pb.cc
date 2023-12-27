// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: failure/failure.proto

#include "failure/failure.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
#include "google/protobuf/generated_message_tctable_impl.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace mavsdk {
namespace rpc {
namespace failure {

inline constexpr InjectRequest::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : failure_unit_{static_cast< ::mavsdk::rpc::failure::FailureUnit >(0)},
        failure_type_{static_cast< ::mavsdk::rpc::failure::FailureType >(0)},
        instance_{0},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR InjectRequest::InjectRequest(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct InjectRequestDefaultTypeInternal {
  PROTOBUF_CONSTEXPR InjectRequestDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~InjectRequestDefaultTypeInternal() {}
  union {
    InjectRequest _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 InjectRequestDefaultTypeInternal _InjectRequest_default_instance_;

inline constexpr FailureResult::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : result_str_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        result_{static_cast< ::mavsdk::rpc::failure::FailureResult_Result >(0)},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR FailureResult::FailureResult(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct FailureResultDefaultTypeInternal {
  PROTOBUF_CONSTEXPR FailureResultDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~FailureResultDefaultTypeInternal() {}
  union {
    FailureResult _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 FailureResultDefaultTypeInternal _FailureResult_default_instance_;

inline constexpr InjectResponse::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : _cached_size_{0},
        failure_result_{nullptr} {}

template <typename>
PROTOBUF_CONSTEXPR InjectResponse::InjectResponse(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct InjectResponseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR InjectResponseDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~InjectResponseDefaultTypeInternal() {}
  union {
    InjectResponse _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 InjectResponseDefaultTypeInternal _InjectResponse_default_instance_;
}  // namespace failure
}  // namespace rpc
}  // namespace mavsdk
static ::_pb::Metadata file_level_metadata_failure_2ffailure_2eproto[3];
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_failure_2ffailure_2eproto[3];
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_failure_2ffailure_2eproto = nullptr;
const ::uint32_t TableStruct_failure_2ffailure_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(
    protodesc_cold) = {
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::mavsdk::rpc::failure::InjectRequest, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::mavsdk::rpc::failure::InjectRequest, _impl_.failure_unit_),
    PROTOBUF_FIELD_OFFSET(::mavsdk::rpc::failure::InjectRequest, _impl_.failure_type_),
    PROTOBUF_FIELD_OFFSET(::mavsdk::rpc::failure::InjectRequest, _impl_.instance_),
    PROTOBUF_FIELD_OFFSET(::mavsdk::rpc::failure::InjectResponse, _impl_._has_bits_),
    PROTOBUF_FIELD_OFFSET(::mavsdk::rpc::failure::InjectResponse, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::mavsdk::rpc::failure::InjectResponse, _impl_.failure_result_),
    0,
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::mavsdk::rpc::failure::FailureResult, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::mavsdk::rpc::failure::FailureResult, _impl_.result_),
    PROTOBUF_FIELD_OFFSET(::mavsdk::rpc::failure::FailureResult, _impl_.result_str_),
};

static const ::_pbi::MigrationSchema
    schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, -1, sizeof(::mavsdk::rpc::failure::InjectRequest)},
        {11, 20, -1, sizeof(::mavsdk::rpc::failure::InjectResponse)},
        {21, -1, -1, sizeof(::mavsdk::rpc::failure::FailureResult)},
};

static const ::_pb::Message* const file_default_instances[] = {
    &::mavsdk::rpc::failure::_InjectRequest_default_instance_._instance,
    &::mavsdk::rpc::failure::_InjectResponse_default_instance_._instance,
    &::mavsdk::rpc::failure::_FailureResult_default_instance_._instance,
};
const char descriptor_table_protodef_failure_2ffailure_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    "\n\025failure/failure.proto\022\022mavsdk.rpc.fail"
    "ure\032\024mavsdk_options.proto\"\217\001\n\rInjectRequ"
    "est\0225\n\014failure_unit\030\001 \001(\0162\037.mavsdk.rpc.f"
    "ailure.FailureUnit\0225\n\014failure_type\030\002 \001(\016"
    "2\037.mavsdk.rpc.failure.FailureType\022\020\n\010ins"
    "tance\030\003 \001(\005\"K\n\016InjectResponse\0229\n\016failure"
    "_result\030\001 \001(\0132!.mavsdk.rpc.failure.Failu"
    "reResult\"\227\002\n\rFailureResult\0228\n\006result\030\001 \001"
    "(\0162(.mavsdk.rpc.failure.FailureResult.Re"
    "sult\022\022\n\nresult_str\030\002 \001(\t\"\267\001\n\006Result\022\022\n\016R"
    "ESULT_UNKNOWN\020\000\022\022\n\016RESULT_SUCCESS\020\001\022\024\n\020R"
    "ESULT_NO_SYSTEM\020\002\022\033\n\027RESULT_CONNECTION_E"
    "RROR\020\003\022\026\n\022RESULT_UNSUPPORTED\020\004\022\021\n\rRESULT"
    "_DENIED\020\005\022\023\n\017RESULT_DISABLED\020\006\022\022\n\016RESULT"
    "_TIMEOUT\020\007*\375\003\n\013FailureUnit\022\034\n\030FAILURE_UN"
    "IT_SENSOR_GYRO\020\000\022\035\n\031FAILURE_UNIT_SENSOR_"
    "ACCEL\020\001\022\033\n\027FAILURE_UNIT_SENSOR_MAG\020\002\022\034\n\030"
    "FAILURE_UNIT_SENSOR_BARO\020\003\022\033\n\027FAILURE_UN"
    "IT_SENSOR_GPS\020\004\022$\n FAILURE_UNIT_SENSOR_O"
    "PTICAL_FLOW\020\005\022\033\n\027FAILURE_UNIT_SENSOR_VIO"
    "\020\006\022\'\n#FAILURE_UNIT_SENSOR_DISTANCE_SENSO"
    "R\020\007\022 \n\034FAILURE_UNIT_SENSOR_AIRSPEED\020\010\022\037\n"
    "\033FAILURE_UNIT_SYSTEM_BATTERY\020d\022\035\n\031FAILUR"
    "E_UNIT_SYSTEM_MOTOR\020e\022\035\n\031FAILURE_UNIT_SY"
    "STEM_SERVO\020f\022!\n\035FAILURE_UNIT_SYSTEM_AVOI"
    "DANCE\020g\022!\n\035FAILURE_UNIT_SYSTEM_RC_SIGNAL"
    "\020h\022&\n\"FAILURE_UNIT_SYSTEM_MAVLINK_SIGNAL"
    "\020i*\322\001\n\013FailureType\022\023\n\017FAILURE_TYPE_OK\020\000\022"
    "\024\n\020FAILURE_TYPE_OFF\020\001\022\026\n\022FAILURE_TYPE_ST"
    "UCK\020\002\022\030\n\024FAILURE_TYPE_GARBAGE\020\003\022\026\n\022FAILU"
    "RE_TYPE_WRONG\020\004\022\025\n\021FAILURE_TYPE_SLOW\020\005\022\030"
    "\n\024FAILURE_TYPE_DELAYED\020\006\022\035\n\031FAILURE_TYPE"
    "_INTERMITTENT\020\0072g\n\016FailureService\022U\n\006Inj"
    "ect\022!.mavsdk.rpc.failure.InjectRequest\032\""
    ".mavsdk.rpc.failure.InjectResponse\"\004\200\265\030\001"
    "B!\n\021io.mavsdk.failureB\014FailureProtob\006pro"
    "to3"
};
static const ::_pbi::DescriptorTable* const descriptor_table_failure_2ffailure_2eproto_deps[1] =
    {
        &::descriptor_table_mavsdk_5foptions_2eproto,
};
static ::absl::once_flag descriptor_table_failure_2ffailure_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_failure_2ffailure_2eproto = {
    false,
    false,
    1443,
    descriptor_table_protodef_failure_2ffailure_2eproto,
    "failure/failure.proto",
    &descriptor_table_failure_2ffailure_2eproto_once,
    descriptor_table_failure_2ffailure_2eproto_deps,
    1,
    3,
    schemas,
    file_default_instances,
    TableStruct_failure_2ffailure_2eproto::offsets,
    file_level_metadata_failure_2ffailure_2eproto,
    file_level_enum_descriptors_failure_2ffailure_2eproto,
    file_level_service_descriptors_failure_2ffailure_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_failure_2ffailure_2eproto_getter() {
  return &descriptor_table_failure_2ffailure_2eproto;
}
// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_failure_2ffailure_2eproto(&descriptor_table_failure_2ffailure_2eproto);
namespace mavsdk {
namespace rpc {
namespace failure {
const ::google::protobuf::EnumDescriptor* FailureResult_Result_descriptor() {
  ::google::protobuf::internal::AssignDescriptors(&descriptor_table_failure_2ffailure_2eproto);
  return file_level_enum_descriptors_failure_2ffailure_2eproto[0];
}
PROTOBUF_CONSTINIT const uint32_t FailureResult_Result_internal_data_[] = {
    524288u, 0u, };
bool FailureResult_Result_IsValid(int value) {
  return 0 <= value && value <= 7;
}
#if (__cplusplus < 201703) && \
  (!defined(_MSC_VER) || (_MSC_VER >= 1900 && _MSC_VER < 1912))

constexpr FailureResult_Result FailureResult::RESULT_UNKNOWN;
constexpr FailureResult_Result FailureResult::RESULT_SUCCESS;
constexpr FailureResult_Result FailureResult::RESULT_NO_SYSTEM;
constexpr FailureResult_Result FailureResult::RESULT_CONNECTION_ERROR;
constexpr FailureResult_Result FailureResult::RESULT_UNSUPPORTED;
constexpr FailureResult_Result FailureResult::RESULT_DENIED;
constexpr FailureResult_Result FailureResult::RESULT_DISABLED;
constexpr FailureResult_Result FailureResult::RESULT_TIMEOUT;
constexpr FailureResult_Result FailureResult::Result_MIN;
constexpr FailureResult_Result FailureResult::Result_MAX;
constexpr int FailureResult::Result_ARRAYSIZE;

#endif  // (__cplusplus < 201703) &&
        // (!defined(_MSC_VER) || (_MSC_VER >= 1900 && _MSC_VER < 1912))
const ::google::protobuf::EnumDescriptor* FailureUnit_descriptor() {
  ::google::protobuf::internal::AssignDescriptors(&descriptor_table_failure_2ffailure_2eproto);
  return file_level_enum_descriptors_failure_2ffailure_2eproto[1];
}
PROTOBUF_CONSTINIT const uint32_t FailureUnit_internal_data_[] = {
    589824u, 128u, 0u, 0u, 4160749568u, 1u, };
bool FailureUnit_IsValid(int value) {
  return ::_pbi::ValidateEnum(value, FailureUnit_internal_data_);
}
const ::google::protobuf::EnumDescriptor* FailureType_descriptor() {
  ::google::protobuf::internal::AssignDescriptors(&descriptor_table_failure_2ffailure_2eproto);
  return file_level_enum_descriptors_failure_2ffailure_2eproto[2];
}
PROTOBUF_CONSTINIT const uint32_t FailureType_internal_data_[] = {
    524288u, 0u, };
bool FailureType_IsValid(int value) {
  return 0 <= value && value <= 7;
}
// ===================================================================

class InjectRequest::_Internal {
 public:
};

InjectRequest::InjectRequest(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:mavsdk.rpc.failure.InjectRequest)
}
InjectRequest::InjectRequest(
    ::google::protobuf::Arena* arena, const InjectRequest& from)
    : InjectRequest(arena) {
  MergeFrom(from);
}
inline PROTOBUF_NDEBUG_INLINE InjectRequest::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : _cached_size_{0} {}

inline void InjectRequest::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  ::memset(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, failure_unit_),
           0,
           offsetof(Impl_, instance_) -
               offsetof(Impl_, failure_unit_) +
               sizeof(Impl_::instance_));
}
InjectRequest::~InjectRequest() {
  // @@protoc_insertion_point(destructor:mavsdk.rpc.failure.InjectRequest)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void InjectRequest::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.~Impl_();
}

PROTOBUF_NOINLINE void InjectRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:mavsdk.rpc.failure.InjectRequest)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&_impl_.failure_unit_, 0, static_cast<::size_t>(
      reinterpret_cast<char*>(&_impl_.instance_) -
      reinterpret_cast<char*>(&_impl_.failure_unit_)) + sizeof(_impl_.instance_));
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* InjectRequest::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<2, 3, 0, 0, 2> InjectRequest::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    3, 24,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967288,  // skipmap
    offsetof(decltype(_table_), field_entries),
    3,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_InjectRequest_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
  }, {{
    {::_pbi::TcParser::MiniParse, {}},
    // .mavsdk.rpc.failure.FailureUnit failure_unit = 1;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(InjectRequest, _impl_.failure_unit_), 63>(),
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(InjectRequest, _impl_.failure_unit_)}},
    // .mavsdk.rpc.failure.FailureType failure_type = 2;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(InjectRequest, _impl_.failure_type_), 63>(),
     {16, 63, 0, PROTOBUF_FIELD_OFFSET(InjectRequest, _impl_.failure_type_)}},
    // int32 instance = 3;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(InjectRequest, _impl_.instance_), 63>(),
     {24, 63, 0, PROTOBUF_FIELD_OFFSET(InjectRequest, _impl_.instance_)}},
  }}, {{
    65535, 65535
  }}, {{
    // .mavsdk.rpc.failure.FailureUnit failure_unit = 1;
    {PROTOBUF_FIELD_OFFSET(InjectRequest, _impl_.failure_unit_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kOpenEnum)},
    // .mavsdk.rpc.failure.FailureType failure_type = 2;
    {PROTOBUF_FIELD_OFFSET(InjectRequest, _impl_.failure_type_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kOpenEnum)},
    // int32 instance = 3;
    {PROTOBUF_FIELD_OFFSET(InjectRequest, _impl_.instance_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt32)},
  }},
  // no aux_entries
  {{
  }},
};

::uint8_t* InjectRequest::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mavsdk.rpc.failure.InjectRequest)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // .mavsdk.rpc.failure.FailureUnit failure_unit = 1;
  if (this->_internal_failure_unit() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
        1, this->_internal_failure_unit(), target);
  }

  // .mavsdk.rpc.failure.FailureType failure_type = 2;
  if (this->_internal_failure_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
        2, this->_internal_failure_type(), target);
  }

  // int32 instance = 3;
  if (this->_internal_instance() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt32ToArrayWithField<3>(
            stream, this->_internal_instance(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mavsdk.rpc.failure.InjectRequest)
  return target;
}

::size_t InjectRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mavsdk.rpc.failure.InjectRequest)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .mavsdk.rpc.failure.FailureUnit failure_unit = 1;
  if (this->_internal_failure_unit() != 0) {
    total_size += 1 +
                  ::_pbi::WireFormatLite::EnumSize(this->_internal_failure_unit());
  }

  // .mavsdk.rpc.failure.FailureType failure_type = 2;
  if (this->_internal_failure_type() != 0) {
    total_size += 1 +
                  ::_pbi::WireFormatLite::EnumSize(this->_internal_failure_type());
  }

  // int32 instance = 3;
  if (this->_internal_instance() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_instance());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::google::protobuf::Message::ClassData InjectRequest::_class_data_ = {
    InjectRequest::MergeImpl,
    nullptr,  // OnDemandRegisterArenaDtor
};
const ::google::protobuf::Message::ClassData* InjectRequest::GetClassData() const {
  return &_class_data_;
}

void InjectRequest::MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg) {
  auto* const _this = static_cast<InjectRequest*>(&to_msg);
  auto& from = static_cast<const InjectRequest&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:mavsdk.rpc.failure.InjectRequest)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_failure_unit() != 0) {
    _this->_internal_set_failure_unit(from._internal_failure_unit());
  }
  if (from._internal_failure_type() != 0) {
    _this->_internal_set_failure_type(from._internal_failure_type());
  }
  if (from._internal_instance() != 0) {
    _this->_internal_set_instance(from._internal_instance());
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void InjectRequest::CopyFrom(const InjectRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mavsdk.rpc.failure.InjectRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool InjectRequest::IsInitialized() const {
  return true;
}

::_pbi::CachedSize* InjectRequest::AccessCachedSize() const {
  return &_impl_._cached_size_;
}
void InjectRequest::InternalSwap(InjectRequest* PROTOBUF_RESTRICT other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::google::protobuf::internal::memswap<
      PROTOBUF_FIELD_OFFSET(InjectRequest, _impl_.instance_)
      + sizeof(InjectRequest::_impl_.instance_)
      - PROTOBUF_FIELD_OFFSET(InjectRequest, _impl_.failure_unit_)>(
          reinterpret_cast<char*>(&_impl_.failure_unit_),
          reinterpret_cast<char*>(&other->_impl_.failure_unit_));
}

::google::protobuf::Metadata InjectRequest::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_failure_2ffailure_2eproto_getter, &descriptor_table_failure_2ffailure_2eproto_once,
      file_level_metadata_failure_2ffailure_2eproto[0]);
}
// ===================================================================

class InjectResponse::_Internal {
 public:
  using HasBits = decltype(std::declval<InjectResponse>()._impl_._has_bits_);
  static constexpr ::int32_t kHasBitsOffset =
    8 * PROTOBUF_FIELD_OFFSET(InjectResponse, _impl_._has_bits_);
  static const ::mavsdk::rpc::failure::FailureResult& failure_result(const InjectResponse* msg);
  static void set_has_failure_result(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

const ::mavsdk::rpc::failure::FailureResult& InjectResponse::_Internal::failure_result(const InjectResponse* msg) {
  return *msg->_impl_.failure_result_;
}
InjectResponse::InjectResponse(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:mavsdk.rpc.failure.InjectResponse)
}
inline PROTOBUF_NDEBUG_INLINE InjectResponse::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : _has_bits_{from._has_bits_},
        _cached_size_{0} {}

InjectResponse::InjectResponse(
    ::google::protobuf::Arena* arena,
    const InjectResponse& from)
    : ::google::protobuf::Message(arena) {
  InjectResponse* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);
  ::uint32_t cached_has_bits = _impl_._has_bits_[0];
  _impl_.failure_result_ = (cached_has_bits & 0x00000001u)
                ? CreateMaybeMessage<::mavsdk::rpc::failure::FailureResult>(arena, *from._impl_.failure_result_)
                : nullptr;

  // @@protoc_insertion_point(copy_constructor:mavsdk.rpc.failure.InjectResponse)
}
inline PROTOBUF_NDEBUG_INLINE InjectResponse::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : _cached_size_{0} {}

inline void InjectResponse::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  _impl_.failure_result_ = {};
}
InjectResponse::~InjectResponse() {
  // @@protoc_insertion_point(destructor:mavsdk.rpc.failure.InjectResponse)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void InjectResponse::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  delete _impl_.failure_result_;
  _impl_.~Impl_();
}

PROTOBUF_NOINLINE void InjectResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:mavsdk.rpc.failure.InjectResponse)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    ABSL_DCHECK(_impl_.failure_result_ != nullptr);
    _impl_.failure_result_->Clear();
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* InjectResponse::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<0, 1, 1, 0, 2> InjectResponse::_table_ = {
  {
    PROTOBUF_FIELD_OFFSET(InjectResponse, _impl_._has_bits_),
    0, // no _extensions_
    1, 0,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967294,  // skipmap
    offsetof(decltype(_table_), field_entries),
    1,  // num_field_entries
    1,  // num_aux_entries
    offsetof(decltype(_table_), aux_entries),
    &_InjectResponse_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
  }, {{
    // .mavsdk.rpc.failure.FailureResult failure_result = 1;
    {::_pbi::TcParser::FastMtS1,
     {10, 0, 0, PROTOBUF_FIELD_OFFSET(InjectResponse, _impl_.failure_result_)}},
  }}, {{
    65535, 65535
  }}, {{
    // .mavsdk.rpc.failure.FailureResult failure_result = 1;
    {PROTOBUF_FIELD_OFFSET(InjectResponse, _impl_.failure_result_), _Internal::kHasBitsOffset + 0, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
  }}, {{
    {::_pbi::TcParser::GetTable<::mavsdk::rpc::failure::FailureResult>()},
  }}, {{
  }},
};

::uint8_t* InjectResponse::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mavsdk.rpc.failure.InjectResponse)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // .mavsdk.rpc.failure.FailureResult failure_result = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::google::protobuf::internal::WireFormatLite::InternalWriteMessage(
        1, _Internal::failure_result(this),
        _Internal::failure_result(this).GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mavsdk.rpc.failure.InjectResponse)
  return target;
}

::size_t InjectResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mavsdk.rpc.failure.InjectResponse)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .mavsdk.rpc.failure.FailureResult failure_result = 1;
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size +=
        1 + ::google::protobuf::internal::WireFormatLite::MessageSize(*_impl_.failure_result_);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::google::protobuf::Message::ClassData InjectResponse::_class_data_ = {
    InjectResponse::MergeImpl,
    nullptr,  // OnDemandRegisterArenaDtor
};
const ::google::protobuf::Message::ClassData* InjectResponse::GetClassData() const {
  return &_class_data_;
}

void InjectResponse::MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg) {
  auto* const _this = static_cast<InjectResponse*>(&to_msg);
  auto& from = static_cast<const InjectResponse&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:mavsdk.rpc.failure.InjectResponse)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if ((from._impl_._has_bits_[0] & 0x00000001u) != 0) {
    _this->_internal_mutable_failure_result()->::mavsdk::rpc::failure::FailureResult::MergeFrom(
        from._internal_failure_result());
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void InjectResponse::CopyFrom(const InjectResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mavsdk.rpc.failure.InjectResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool InjectResponse::IsInitialized() const {
  return true;
}

::_pbi::CachedSize* InjectResponse::AccessCachedSize() const {
  return &_impl_._cached_size_;
}
void InjectResponse::InternalSwap(InjectResponse* PROTOBUF_RESTRICT other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  swap(_impl_.failure_result_, other->_impl_.failure_result_);
}

::google::protobuf::Metadata InjectResponse::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_failure_2ffailure_2eproto_getter, &descriptor_table_failure_2ffailure_2eproto_once,
      file_level_metadata_failure_2ffailure_2eproto[1]);
}
// ===================================================================

class FailureResult::_Internal {
 public:
};

FailureResult::FailureResult(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:mavsdk.rpc.failure.FailureResult)
}
inline PROTOBUF_NDEBUG_INLINE FailureResult::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : result_str_(arena, from.result_str_),
        _cached_size_{0} {}

FailureResult::FailureResult(
    ::google::protobuf::Arena* arena,
    const FailureResult& from)
    : ::google::protobuf::Message(arena) {
  FailureResult* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);
  _impl_.result_ = from._impl_.result_;

  // @@protoc_insertion_point(copy_constructor:mavsdk.rpc.failure.FailureResult)
}
inline PROTOBUF_NDEBUG_INLINE FailureResult::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : result_str_(arena),
        _cached_size_{0} {}

inline void FailureResult::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  _impl_.result_ = {};
}
FailureResult::~FailureResult() {
  // @@protoc_insertion_point(destructor:mavsdk.rpc.failure.FailureResult)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void FailureResult::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.result_str_.Destroy();
  _impl_.~Impl_();
}

PROTOBUF_NOINLINE void FailureResult::Clear() {
// @@protoc_insertion_point(message_clear_start:mavsdk.rpc.failure.FailureResult)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.result_str_.ClearToEmpty();
  _impl_.result_ = 0;
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* FailureResult::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<1, 2, 0, 51, 2> FailureResult::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    2, 8,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967292,  // skipmap
    offsetof(decltype(_table_), field_entries),
    2,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_FailureResult_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
  }, {{
    // string result_str = 2;
    {::_pbi::TcParser::FastUS1,
     {18, 63, 0, PROTOBUF_FIELD_OFFSET(FailureResult, _impl_.result_str_)}},
    // .mavsdk.rpc.failure.FailureResult.Result result = 1;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(FailureResult, _impl_.result_), 63>(),
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(FailureResult, _impl_.result_)}},
  }}, {{
    65535, 65535
  }}, {{
    // .mavsdk.rpc.failure.FailureResult.Result result = 1;
    {PROTOBUF_FIELD_OFFSET(FailureResult, _impl_.result_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kOpenEnum)},
    // string result_str = 2;
    {PROTOBUF_FIELD_OFFSET(FailureResult, _impl_.result_str_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\40\0\12\0\0\0\0\0"
    "mavsdk.rpc.failure.FailureResult"
    "result_str"
  }},
};

::uint8_t* FailureResult::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mavsdk.rpc.failure.FailureResult)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // .mavsdk.rpc.failure.FailureResult.Result result = 1;
  if (this->_internal_result() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
        1, this->_internal_result(), target);
  }

  // string result_str = 2;
  if (!this->_internal_result_str().empty()) {
    const std::string& _s = this->_internal_result_str();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "mavsdk.rpc.failure.FailureResult.result_str");
    target = stream->WriteStringMaybeAliased(2, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mavsdk.rpc.failure.FailureResult)
  return target;
}

::size_t FailureResult::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mavsdk.rpc.failure.FailureResult)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string result_str = 2;
  if (!this->_internal_result_str().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_result_str());
  }

  // .mavsdk.rpc.failure.FailureResult.Result result = 1;
  if (this->_internal_result() != 0) {
    total_size += 1 +
                  ::_pbi::WireFormatLite::EnumSize(this->_internal_result());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::google::protobuf::Message::ClassData FailureResult::_class_data_ = {
    FailureResult::MergeImpl,
    nullptr,  // OnDemandRegisterArenaDtor
};
const ::google::protobuf::Message::ClassData* FailureResult::GetClassData() const {
  return &_class_data_;
}

void FailureResult::MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg) {
  auto* const _this = static_cast<FailureResult*>(&to_msg);
  auto& from = static_cast<const FailureResult&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:mavsdk.rpc.failure.FailureResult)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_result_str().empty()) {
    _this->_internal_set_result_str(from._internal_result_str());
  }
  if (from._internal_result() != 0) {
    _this->_internal_set_result(from._internal_result());
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void FailureResult::CopyFrom(const FailureResult& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mavsdk.rpc.failure.FailureResult)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool FailureResult::IsInitialized() const {
  return true;
}

::_pbi::CachedSize* FailureResult::AccessCachedSize() const {
  return &_impl_._cached_size_;
}
void FailureResult::InternalSwap(FailureResult* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.result_str_, &other->_impl_.result_str_, arena);
  swap(_impl_.result_, other->_impl_.result_);
}

::google::protobuf::Metadata FailureResult::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_failure_2ffailure_2eproto_getter, &descriptor_table_failure_2ffailure_2eproto_once,
      file_level_metadata_failure_2ffailure_2eproto[2]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace failure
}  // namespace rpc
}  // namespace mavsdk
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"
