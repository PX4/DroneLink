// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: mavsdk_options.proto
// Protobuf C++ Version: 5.29.1

#include "mavsdk_options.pb.h"

#include <algorithm>
#include <type_traits>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/generated_message_tctable_impl.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace mavsdk {
namespace options {} // namespace options
} // namespace mavsdk
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_mavsdk_5foptions_2eproto[1];
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_mavsdk_5foptions_2eproto = nullptr;
const ::uint32_t TableStruct_mavsdk_5foptions_2eproto::offsets[1] = {};
static constexpr ::_pbi::MigrationSchema* schemas = nullptr;
static constexpr ::_pb::Message* const* file_default_instances = nullptr;
const char descriptor_table_protodef_mavsdk_5foptions_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n\024mavsdk_options.proto\022\016mavsdk.options\032 "
    "google/protobuf/descriptor.proto**\n\tAsyn"
    "cType\022\t\n\005ASYNC\020\000\022\010\n\004SYNC\020\001\022\010\n\004BOTH\020\002:6\n\r"
    "default_value\022\035.google.protobuf.FieldOpt"
    "ions\030\320\206\003 \001(\t:0\n\007epsilon\022\035.google.protobu"
    "f.FieldOptions\030\321\206\003 \001(\001:O\n\nasync_type\022\036.g"
    "oogle.protobuf.MethodOptions\030\320\206\003 \001(\0162\031.m"
    "avsdk.options.AsyncType:3\n\tis_finite\022\036.g"
    "oogle.protobuf.MethodOptions\030\321\206\003 \001(\010B\020\n\016"
    "options.mavsdkb\006proto3"};
static const ::_pbi::DescriptorTable* const descriptor_table_mavsdk_5foptions_2eproto_deps[1] = {
    &::descriptor_table_google_2fprotobuf_2fdescriptor_2eproto,
};
static ::absl::once_flag descriptor_table_mavsdk_5foptions_2eproto_once;
PROTOBUF_CONSTINIT const ::_pbi::DescriptorTable descriptor_table_mavsdk_5foptions_2eproto = {
    false,
    false,
    382,
    descriptor_table_protodef_mavsdk_5foptions_2eproto,
    "mavsdk_options.proto",
    &descriptor_table_mavsdk_5foptions_2eproto_once,
    descriptor_table_mavsdk_5foptions_2eproto_deps,
    1,
    0,
    schemas,
    file_default_instances,
    TableStruct_mavsdk_5foptions_2eproto::offsets,
    file_level_enum_descriptors_mavsdk_5foptions_2eproto,
    file_level_service_descriptors_mavsdk_5foptions_2eproto,
};
namespace mavsdk {
namespace options {
const ::google::protobuf::EnumDescriptor* AsyncType_descriptor()
{
    ::google::protobuf::internal::AssignDescriptors(&descriptor_table_mavsdk_5foptions_2eproto);
    return file_level_enum_descriptors_mavsdk_5foptions_2eproto[0];
}
PROTOBUF_CONSTINIT const uint32_t AsyncType_internal_data_[] = {
    196608u,
    0u,
};
bool AsyncType_IsValid(int value)
{
    return 0 <= value && value <= 2;
}
const std::string default_value_default("");
PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 ::_pbi::
    ExtensionIdentifier<::google::protobuf::FieldOptions, ::_pbi::StringTypeTraits, 9, false>
        default_value(kDefaultValueFieldNumber, default_value_default);
PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 ::_pbi::ExtensionIdentifier<
    ::google::protobuf::FieldOptions,
    ::_pbi::PrimitiveTypeTraits<double>,
    1,
    false>
    epsilon(kEpsilonFieldNumber, 0);
PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 ::_pbi::ExtensionIdentifier<
    ::google::protobuf::MethodOptions,
    ::_pbi::EnumTypeTraits<::mavsdk::options::AsyncType, ::mavsdk::options::AsyncType_IsValid>,
    14,
    false>
    async_type(kAsyncTypeFieldNumber, static_cast<::mavsdk::options::AsyncType>(0));
PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 ::_pbi::ExtensionIdentifier<
    ::google::protobuf::MethodOptions,
    ::_pbi::PrimitiveTypeTraits<bool>,
    8,
    false>
    is_finite(kIsFiniteFieldNumber, false);
// @@protoc_insertion_point(namespace_scope)
} // namespace options
} // namespace mavsdk
namespace google {
namespace protobuf {} // namespace protobuf
} // namespace google
// @@protoc_insertion_point(global_scope)
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::std::false_type _static_init2_ PROTOBUF_UNUSED =
    (::_pbi::AddDescriptors(&descriptor_table_mavsdk_5foptions_2eproto),
     ::_pbi::ExtensionSet::RegisterExtension(
         &::google::protobuf::FieldOptions::default_instance(), 50000, 9, false, false),
     ::_pbi::ExtensionSet::RegisterExtension(
         &::google::protobuf::FieldOptions::default_instance(), 50001, 1, false, false),
     ::_pbi::ExtensionSet::RegisterEnumExtension(
         &::google::protobuf::MethodOptions::default_instance(),
         50000,
         14,
         false,
         false,
         ::mavsdk::options::AsyncType_IsValid),
     ::_pbi::ExtensionSet::RegisterExtension(
         &::google::protobuf::MethodOptions::default_instance(), 50001, 8, false, false),
     ::std::false_type{});
#include "google/protobuf/port_undef.inc"
