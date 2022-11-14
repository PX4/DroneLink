// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/info/info.proto)

#include "info/info.grpc.pb.h"
#include "plugins/info/info.h"

#include "mavsdk.h"

#include "lazy_plugin.h"

#include "log.h"
#include <atomic>
#include <cmath>
#include <future>
#include <limits>
#include <memory>
#include <sstream>
#include <vector>

namespace mavsdk {
namespace mavsdk_server {

template<typename Info = Info, typename LazyPlugin = LazyPlugin<Info>>

class InfoServiceImpl final : public rpc::info::InfoService::Service {
public:
    InfoServiceImpl(LazyPlugin& lazy_plugin) : _lazy_plugin(lazy_plugin) {}

    template<typename ResponseType>
    void fillResponseWithResult(ResponseType* response, mavsdk::Info::Result& result) const
    {
        auto rpc_result = translateToRpcResult(result);

        auto* rpc_info_result = new rpc::info::InfoResult();
        rpc_info_result->set_result(rpc_result);
        std::stringstream ss;
        ss << result;
        rpc_info_result->set_result_str(ss.str());

        response->set_allocated_info_result(rpc_info_result);
    }

    static std::unique_ptr<rpc::info::FlightInfo>
    translateToRpcFlightInfo(const mavsdk::Info::FlightInfo& flight_info)
    {
        auto rpc_obj = std::make_unique<rpc::info::FlightInfo>();

        rpc_obj->set_time_boot_ms(flight_info.time_boot_ms);

        rpc_obj->set_flight_uid(flight_info.flight_uid);

        return rpc_obj;
    }

    static mavsdk::Info::FlightInfo
    translateFromRpcFlightInfo(const rpc::info::FlightInfo& flight_info)
    {
        mavsdk::Info::FlightInfo obj;

        obj.time_boot_ms = flight_info.time_boot_ms();

        obj.flight_uid = flight_info.flight_uid();

        return obj;
    }

    static std::unique_ptr<rpc::info::Identification>
    translateToRpcIdentification(const mavsdk::Info::Identification& identification)
    {
        auto rpc_obj = std::make_unique<rpc::info::Identification>();

        rpc_obj->set_hardware_uid(identification.hardware_uid);

        rpc_obj->set_legacy_uid(identification.legacy_uid);

        return rpc_obj;
    }

    static mavsdk::Info::Identification
    translateFromRpcIdentification(const rpc::info::Identification& identification)
    {
        mavsdk::Info::Identification obj;

        obj.hardware_uid = identification.hardware_uid();

        obj.legacy_uid = identification.legacy_uid();

        return obj;
    }

    static rpc::info::Capabilities::ProtocolCapability translateToRpcProtocolCapability(
        const mavsdk::Info::Capabilities::ProtocolCapability& protocol_capability)
    {
        switch (protocol_capability) {
            default:
                LogErr() << "Unknown protocol_capability enum value: "
                         << static_cast<int>(protocol_capability);
            // FALLTHROUGH
            case mavsdk::Info::Capabilities::ProtocolCapability::Unknown:
                return rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_UNKNOWN;
            case mavsdk::Info::Capabilities::ProtocolCapability::MissionFloat:
                return rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_MISSION_FLOAT;
            case mavsdk::Info::Capabilities::ProtocolCapability::ParamFloat:
                return rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_PARAM_FLOAT;
            case mavsdk::Info::Capabilities::ProtocolCapability::MissionInt:
                return rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_MISSION_INT;
            case mavsdk::Info::Capabilities::ProtocolCapability::CommandInt:
                return rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_COMMAND_INT;
            case mavsdk::Info::Capabilities::ProtocolCapability::ParamEncodeBytewise:
                return rpc::info::
                    Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_PARAM_ENCODE_BYTEWISE;
            case mavsdk::Info::Capabilities::ProtocolCapability::Ftp:
                return rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_FTP;
            case mavsdk::Info::Capabilities::ProtocolCapability::SetAttitudeTarget:
                return rpc::info::
                    Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_SET_ATTITUDE_TARGET;
            case mavsdk::Info::Capabilities::ProtocolCapability::SetPositionTargetLocalNed:
                return rpc::info::
                    Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_SET_POSITION_TARGET_LOCAL_NED;
            case mavsdk::Info::Capabilities::ProtocolCapability::SetPositionTargetGlobalInt:
                return rpc::info::
                    Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_SET_POSITION_TARGET_GLOBAL_INT;
            case mavsdk::Info::Capabilities::ProtocolCapability::Terrain:
                return rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_TERRAIN;
            case mavsdk::Info::Capabilities::ProtocolCapability::SetActuatorTarget:
                return rpc::info::
                    Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_SET_ACTUATOR_TARGET;
            case mavsdk::Info::Capabilities::ProtocolCapability::FlightTermination:
                return rpc::info::
                    Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_FLIGHT_TERMINATION;
            case mavsdk::Info::Capabilities::ProtocolCapability::CompassCalibration:
                return rpc::info::
                    Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_COMPASS_CALIBRATION;
            case mavsdk::Info::Capabilities::ProtocolCapability::Mavlink2:
                return rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_MAVLINK2;
            case mavsdk::Info::Capabilities::ProtocolCapability::MissionFence:
                return rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_MISSION_FENCE;
            case mavsdk::Info::Capabilities::ProtocolCapability::MissionRally:
                return rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_MISSION_RALLY;
            case mavsdk::Info::Capabilities::ProtocolCapability::Reserved2:
                return rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_RESERVED2;
            case mavsdk::Info::Capabilities::ProtocolCapability::ParamEncodeCCast:
                return rpc::info::
                    Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_PARAM_ENCODE_C_CAST;
        }
    }

    static mavsdk::Info::Capabilities::ProtocolCapability translateFromRpcProtocolCapability(
        const rpc::info::Capabilities::ProtocolCapability protocol_capability)
    {
        switch (protocol_capability) {
            default:
                LogErr() << "Unknown protocol_capability enum value: "
                         << static_cast<int>(protocol_capability);
            // FALLTHROUGH
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_UNKNOWN:
                return mavsdk::Info::Capabilities::ProtocolCapability::Unknown;
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_MISSION_FLOAT:
                return mavsdk::Info::Capabilities::ProtocolCapability::MissionFloat;
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_PARAM_FLOAT:
                return mavsdk::Info::Capabilities::ProtocolCapability::ParamFloat;
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_MISSION_INT:
                return mavsdk::Info::Capabilities::ProtocolCapability::MissionInt;
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_COMMAND_INT:
                return mavsdk::Info::Capabilities::ProtocolCapability::CommandInt;
            case rpc::info::
                Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_PARAM_ENCODE_BYTEWISE:
                return mavsdk::Info::Capabilities::ProtocolCapability::ParamEncodeBytewise;
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_FTP:
                return mavsdk::Info::Capabilities::ProtocolCapability::Ftp;
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_SET_ATTITUDE_TARGET:
                return mavsdk::Info::Capabilities::ProtocolCapability::SetAttitudeTarget;
            case rpc::info::
                Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_SET_POSITION_TARGET_LOCAL_NED:
                return mavsdk::Info::Capabilities::ProtocolCapability::SetPositionTargetLocalNed;
            case rpc::info::
                Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_SET_POSITION_TARGET_GLOBAL_INT:
                return mavsdk::Info::Capabilities::ProtocolCapability::SetPositionTargetGlobalInt;
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_TERRAIN:
                return mavsdk::Info::Capabilities::ProtocolCapability::Terrain;
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_SET_ACTUATOR_TARGET:
                return mavsdk::Info::Capabilities::ProtocolCapability::SetActuatorTarget;
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_FLIGHT_TERMINATION:
                return mavsdk::Info::Capabilities::ProtocolCapability::FlightTermination;
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_COMPASS_CALIBRATION:
                return mavsdk::Info::Capabilities::ProtocolCapability::CompassCalibration;
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_MAVLINK2:
                return mavsdk::Info::Capabilities::ProtocolCapability::Mavlink2;
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_MISSION_FENCE:
                return mavsdk::Info::Capabilities::ProtocolCapability::MissionFence;
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_MISSION_RALLY:
                return mavsdk::Info::Capabilities::ProtocolCapability::MissionRally;
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_RESERVED2:
                return mavsdk::Info::Capabilities::ProtocolCapability::Reserved2;
            case rpc::info::Capabilities_ProtocolCapability_PROTOCOL_CAPABILITY_PARAM_ENCODE_C_CAST:
                return mavsdk::Info::Capabilities::ProtocolCapability::ParamEncodeCCast;
        }
    }

    static std::unique_ptr<rpc::info::Capabilities>
    translateToRpcCapabilities(const mavsdk::Info::Capabilities& capabilities)
    {
        auto rpc_obj = std::make_unique<rpc::info::Capabilities>();

        rpc_obj->set_capabilities(capabilities.capabilities);

        return rpc_obj;
    }

    static mavsdk::Info::Capabilities
    translateFromRpcCapabilities(const rpc::info::Capabilities& capabilities)
    {
        mavsdk::Info::Capabilities obj;

        obj.capabilities = capabilities.capabilities();

        return obj;
    }

    static std::unique_ptr<rpc::info::Product>
    translateToRpcProduct(const mavsdk::Info::Product& product)
    {
        auto rpc_obj = std::make_unique<rpc::info::Product>();

        rpc_obj->set_vendor_id(product.vendor_id);

        rpc_obj->set_vendor_name(product.vendor_name);

        rpc_obj->set_product_id(product.product_id);

        rpc_obj->set_product_name(product.product_name);

        return rpc_obj;
    }

    static mavsdk::Info::Product translateFromRpcProduct(const rpc::info::Product& product)
    {
        mavsdk::Info::Product obj;

        obj.vendor_id = product.vendor_id();

        obj.vendor_name = product.vendor_name();

        obj.product_id = product.product_id();

        obj.product_name = product.product_name();

        return obj;
    }

    static rpc::info::Version::FlightSoftwareVersionType translateToRpcFlightSoftwareVersionType(
        const mavsdk::Info::Version::FlightSoftwareVersionType& flight_software_version_type)
    {
        switch (flight_software_version_type) {
            default:
                LogErr() << "Unknown flight_software_version_type enum value: "
                         << static_cast<int>(flight_software_version_type);
            // FALLTHROUGH
            case mavsdk::Info::Version::FlightSoftwareVersionType::Unknown:
                return rpc::info::
                    Version_FlightSoftwareVersionType_FLIGHT_SOFTWARE_VERSION_TYPE_UNKNOWN;
            case mavsdk::Info::Version::FlightSoftwareVersionType::Dev:
                return rpc::info::
                    Version_FlightSoftwareVersionType_FLIGHT_SOFTWARE_VERSION_TYPE_DEV;
            case mavsdk::Info::Version::FlightSoftwareVersionType::Alpha:
                return rpc::info::
                    Version_FlightSoftwareVersionType_FLIGHT_SOFTWARE_VERSION_TYPE_ALPHA;
            case mavsdk::Info::Version::FlightSoftwareVersionType::Beta:
                return rpc::info::
                    Version_FlightSoftwareVersionType_FLIGHT_SOFTWARE_VERSION_TYPE_BETA;
            case mavsdk::Info::Version::FlightSoftwareVersionType::Rc:
                return rpc::info::Version_FlightSoftwareVersionType_FLIGHT_SOFTWARE_VERSION_TYPE_RC;
            case mavsdk::Info::Version::FlightSoftwareVersionType::Release:
                return rpc::info::
                    Version_FlightSoftwareVersionType_FLIGHT_SOFTWARE_VERSION_TYPE_RELEASE;
        }
    }

    static mavsdk::Info::Version::FlightSoftwareVersionType
    translateFromRpcFlightSoftwareVersionType(
        const rpc::info::Version::FlightSoftwareVersionType flight_software_version_type)
    {
        switch (flight_software_version_type) {
            default:
                LogErr() << "Unknown flight_software_version_type enum value: "
                         << static_cast<int>(flight_software_version_type);
            // FALLTHROUGH
            case rpc::info::Version_FlightSoftwareVersionType_FLIGHT_SOFTWARE_VERSION_TYPE_UNKNOWN:
                return mavsdk::Info::Version::FlightSoftwareVersionType::Unknown;
            case rpc::info::Version_FlightSoftwareVersionType_FLIGHT_SOFTWARE_VERSION_TYPE_DEV:
                return mavsdk::Info::Version::FlightSoftwareVersionType::Dev;
            case rpc::info::Version_FlightSoftwareVersionType_FLIGHT_SOFTWARE_VERSION_TYPE_ALPHA:
                return mavsdk::Info::Version::FlightSoftwareVersionType::Alpha;
            case rpc::info::Version_FlightSoftwareVersionType_FLIGHT_SOFTWARE_VERSION_TYPE_BETA:
                return mavsdk::Info::Version::FlightSoftwareVersionType::Beta;
            case rpc::info::Version_FlightSoftwareVersionType_FLIGHT_SOFTWARE_VERSION_TYPE_RC:
                return mavsdk::Info::Version::FlightSoftwareVersionType::Rc;
            case rpc::info::Version_FlightSoftwareVersionType_FLIGHT_SOFTWARE_VERSION_TYPE_RELEASE:
                return mavsdk::Info::Version::FlightSoftwareVersionType::Release;
        }
    }

    static std::unique_ptr<rpc::info::Version>
    translateToRpcVersion(const mavsdk::Info::Version& version)
    {
        auto rpc_obj = std::make_unique<rpc::info::Version>();

        rpc_obj->set_flight_sw_major(version.flight_sw_major);

        rpc_obj->set_flight_sw_minor(version.flight_sw_minor);

        rpc_obj->set_flight_sw_patch(version.flight_sw_patch);

        rpc_obj->set_flight_sw_vendor_major(version.flight_sw_vendor_major);

        rpc_obj->set_flight_sw_vendor_minor(version.flight_sw_vendor_minor);

        rpc_obj->set_flight_sw_vendor_patch(version.flight_sw_vendor_patch);

        rpc_obj->set_os_sw_major(version.os_sw_major);

        rpc_obj->set_os_sw_minor(version.os_sw_minor);

        rpc_obj->set_os_sw_patch(version.os_sw_patch);

        rpc_obj->set_flight_sw_git_hash(version.flight_sw_git_hash);

        rpc_obj->set_os_sw_git_hash(version.os_sw_git_hash);

        rpc_obj->set_flight_sw_version_type(
            translateToRpcFlightSoftwareVersionType(version.flight_sw_version_type));

        return rpc_obj;
    }

    static mavsdk::Info::Version translateFromRpcVersion(const rpc::info::Version& version)
    {
        mavsdk::Info::Version obj;

        obj.flight_sw_major = version.flight_sw_major();

        obj.flight_sw_minor = version.flight_sw_minor();

        obj.flight_sw_patch = version.flight_sw_patch();

        obj.flight_sw_vendor_major = version.flight_sw_vendor_major();

        obj.flight_sw_vendor_minor = version.flight_sw_vendor_minor();

        obj.flight_sw_vendor_patch = version.flight_sw_vendor_patch();

        obj.os_sw_major = version.os_sw_major();

        obj.os_sw_minor = version.os_sw_minor();

        obj.os_sw_patch = version.os_sw_patch();

        obj.flight_sw_git_hash = version.flight_sw_git_hash();

        obj.os_sw_git_hash = version.os_sw_git_hash();

        obj.flight_sw_version_type =
            translateFromRpcFlightSoftwareVersionType(version.flight_sw_version_type());

        return obj;
    }

    static rpc::info::InfoResult::Result translateToRpcResult(const mavsdk::Info::Result& result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case mavsdk::Info::Result::Unknown:
                return rpc::info::InfoResult_Result_RESULT_UNKNOWN;
            case mavsdk::Info::Result::Success:
                return rpc::info::InfoResult_Result_RESULT_SUCCESS;
            case mavsdk::Info::Result::InformationNotReceivedYet:
                return rpc::info::InfoResult_Result_RESULT_INFORMATION_NOT_RECEIVED_YET;
            case mavsdk::Info::Result::NoSystem:
                return rpc::info::InfoResult_Result_RESULT_NO_SYSTEM;
        }
    }

    static mavsdk::Info::Result translateFromRpcResult(const rpc::info::InfoResult::Result result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case rpc::info::InfoResult_Result_RESULT_UNKNOWN:
                return mavsdk::Info::Result::Unknown;
            case rpc::info::InfoResult_Result_RESULT_SUCCESS:
                return mavsdk::Info::Result::Success;
            case rpc::info::InfoResult_Result_RESULT_INFORMATION_NOT_RECEIVED_YET:
                return mavsdk::Info::Result::InformationNotReceivedYet;
            case rpc::info::InfoResult_Result_RESULT_NO_SYSTEM:
                return mavsdk::Info::Result::NoSystem;
        }
    }

    grpc::Status GetFlightInformation(
        grpc::ServerContext* /* context */,
        const rpc::info::GetFlightInformationRequest* /* request */,
        rpc::info::GetFlightInformationResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Info::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->get_flight_information();

        if (response != nullptr) {
            fillResponseWithResult(response, result.first);

            response->set_allocated_flight_info(translateToRpcFlightInfo(result.second).release());
        }

        return grpc::Status::OK;
    }

    grpc::Status GetIdentification(
        grpc::ServerContext* /* context */,
        const rpc::info::GetIdentificationRequest* /* request */,
        rpc::info::GetIdentificationResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Info::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->get_identification();

        if (response != nullptr) {
            fillResponseWithResult(response, result.first);

            response->set_allocated_identification(
                translateToRpcIdentification(result.second).release());
        }

        return grpc::Status::OK;
    }

    grpc::Status GetCapabilities(
        grpc::ServerContext* /* context */,
        const rpc::info::GetCapabilitiesRequest* /* request */,
        rpc::info::GetCapabilitiesResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Info::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->get_capabilities();

        if (response != nullptr) {
            fillResponseWithResult(response, result.first);

            response->set_allocated_capabilities(
                translateToRpcCapabilities(result.second).release());
        }

        return grpc::Status::OK;
    }

    grpc::Status GetProduct(
        grpc::ServerContext* /* context */,
        const rpc::info::GetProductRequest* /* request */,
        rpc::info::GetProductResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Info::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->get_product();

        if (response != nullptr) {
            fillResponseWithResult(response, result.first);

            response->set_allocated_product(translateToRpcProduct(result.second).release());
        }

        return grpc::Status::OK;
    }

    grpc::Status GetVersion(
        grpc::ServerContext* /* context */,
        const rpc::info::GetVersionRequest* /* request */,
        rpc::info::GetVersionResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Info::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->get_version();

        if (response != nullptr) {
            fillResponseWithResult(response, result.first);

            response->set_allocated_version(translateToRpcVersion(result.second).release());
        }

        return grpc::Status::OK;
    }

    grpc::Status GetSpeedFactor(
        grpc::ServerContext* /* context */,
        const rpc::info::GetSpeedFactorRequest* /* request */,
        rpc::info::GetSpeedFactorResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Info::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->get_speed_factor();

        if (response != nullptr) {
            fillResponseWithResult(response, result.first);

            response->set_speed_factor(result.second);
        }

        return grpc::Status::OK;
    }

    void stop()
    {
        _stopped.store(true);
        for (auto& prom : _stream_stop_promises) {
            if (auto handle = prom.lock()) {
                handle->set_value();
            }
        }
    }

private:
    void register_stream_stop_promise(std::weak_ptr<std::promise<void>> prom)
    {
        // If we have already stopped, set promise immediately and don't add it to list.
        if (_stopped.load()) {
            if (auto handle = prom.lock()) {
                handle->set_value();
            }
        } else {
            _stream_stop_promises.push_back(prom);
        }
    }

    void unregister_stream_stop_promise(std::shared_ptr<std::promise<void>> prom)
    {
        for (auto it = _stream_stop_promises.begin(); it != _stream_stop_promises.end();
             /* ++it */) {
            if (it->lock() == prom) {
                it = _stream_stop_promises.erase(it);
            } else {
                ++it;
            }
        }
    }

    LazyPlugin& _lazy_plugin;

    std::atomic<bool> _stopped{false};
    std::vector<std::weak_ptr<std::promise<void>>> _stream_stop_promises{};
};

} // namespace mavsdk_server
} // namespace mavsdk