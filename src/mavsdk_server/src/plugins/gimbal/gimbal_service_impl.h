// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/gimbal/gimbal.proto)

#include "gimbal/gimbal.grpc.pb.h"
#include "plugins/gimbal/gimbal.h"

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

template<typename Gimbal = Gimbal, typename LazyPlugin = LazyPlugin<Gimbal>>

class GimbalServiceImpl final : public rpc::gimbal::GimbalService::Service {
public:
    GimbalServiceImpl(LazyPlugin& lazy_plugin) : _lazy_plugin(lazy_plugin) {}

    template<typename ResponseType>
    void fillResponseWithResult(ResponseType* response, mavsdk::Gimbal::Result& result) const
    {
        auto rpc_result = translateToRpcResult(result);

        auto* rpc_gimbal_result = new rpc::gimbal::GimbalResult();
        rpc_gimbal_result->set_result(rpc_result);
        std::stringstream ss;
        ss << result;
        rpc_gimbal_result->set_result_str(ss.str());

        response->set_allocated_gimbal_result(rpc_gimbal_result);
    }

    static rpc::gimbal::GimbalMode
    translateToRpcGimbalMode(const mavsdk::Gimbal::GimbalMode& gimbal_mode)
    {
        switch (gimbal_mode) {
            default:
                LogErr() << "Unknown gimbal_mode enum value: " << static_cast<int>(gimbal_mode);
            // FALLTHROUGH
            case mavsdk::Gimbal::GimbalMode::YawFollow:
                return rpc::gimbal::GIMBAL_MODE_YAW_FOLLOW;
            case mavsdk::Gimbal::GimbalMode::YawLock:
                return rpc::gimbal::GIMBAL_MODE_YAW_LOCK;
        }
    }

    static mavsdk::Gimbal::GimbalMode
    translateFromRpcGimbalMode(const rpc::gimbal::GimbalMode gimbal_mode)
    {
        switch (gimbal_mode) {
            default:
                LogErr() << "Unknown gimbal_mode enum value: " << static_cast<int>(gimbal_mode);
            // FALLTHROUGH
            case rpc::gimbal::GIMBAL_MODE_YAW_FOLLOW:
                return mavsdk::Gimbal::GimbalMode::YawFollow;
            case rpc::gimbal::GIMBAL_MODE_YAW_LOCK:
                return mavsdk::Gimbal::GimbalMode::YawLock;
        }
    }

    static rpc::gimbal::ControlMode
    translateToRpcControlMode(const mavsdk::Gimbal::ControlMode& control_mode)
    {
        switch (control_mode) {
            default:
                LogErr() << "Unknown control_mode enum value: " << static_cast<int>(control_mode);
            // FALLTHROUGH
            case mavsdk::Gimbal::ControlMode::None:
                return rpc::gimbal::CONTROL_MODE_NONE;
            case mavsdk::Gimbal::ControlMode::Primary:
                return rpc::gimbal::CONTROL_MODE_PRIMARY;
            case mavsdk::Gimbal::ControlMode::Secondary:
                return rpc::gimbal::CONTROL_MODE_SECONDARY;
        }
    }

    static mavsdk::Gimbal::ControlMode
    translateFromRpcControlMode(const rpc::gimbal::ControlMode control_mode)
    {
        switch (control_mode) {
            default:
                LogErr() << "Unknown control_mode enum value: " << static_cast<int>(control_mode);
            // FALLTHROUGH
            case rpc::gimbal::CONTROL_MODE_NONE:
                return mavsdk::Gimbal::ControlMode::None;
            case rpc::gimbal::CONTROL_MODE_PRIMARY:
                return mavsdk::Gimbal::ControlMode::Primary;
            case rpc::gimbal::CONTROL_MODE_SECONDARY:
                return mavsdk::Gimbal::ControlMode::Secondary;
        }
    }

    static std::unique_ptr<rpc::gimbal::ControlStatus>
    translateToRpcControlStatus(const mavsdk::Gimbal::ControlStatus& control_status)
    {
        auto rpc_obj = std::make_unique<rpc::gimbal::ControlStatus>();

        rpc_obj->set_control_mode(translateToRpcControlMode(control_status.control_mode));

        rpc_obj->set_sysid_primary_control(control_status.sysid_primary_control);

        rpc_obj->set_compid_primary_control(control_status.compid_primary_control);

        rpc_obj->set_sysid_secondary_control(control_status.sysid_secondary_control);

        rpc_obj->set_compid_secondary_control(control_status.compid_secondary_control);

        return rpc_obj;
    }

    static mavsdk::Gimbal::ControlStatus
    translateFromRpcControlStatus(const rpc::gimbal::ControlStatus& control_status)
    {
        mavsdk::Gimbal::ControlStatus obj;

        obj.control_mode = translateFromRpcControlMode(control_status.control_mode());

        obj.sysid_primary_control = control_status.sysid_primary_control();

        obj.compid_primary_control = control_status.compid_primary_control();

        obj.sysid_secondary_control = control_status.sysid_secondary_control();

        obj.compid_secondary_control = control_status.compid_secondary_control();

        return obj;
    }

    static rpc::gimbal::GimbalResult::Result
    translateToRpcResult(const mavsdk::Gimbal::Result& result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case mavsdk::Gimbal::Result::Unknown:
                return rpc::gimbal::GimbalResult_Result_RESULT_UNKNOWN;
            case mavsdk::Gimbal::Result::Success:
                return rpc::gimbal::GimbalResult_Result_RESULT_SUCCESS;
            case mavsdk::Gimbal::Result::Error:
                return rpc::gimbal::GimbalResult_Result_RESULT_ERROR;
            case mavsdk::Gimbal::Result::Timeout:
                return rpc::gimbal::GimbalResult_Result_RESULT_TIMEOUT;
            case mavsdk::Gimbal::Result::Unsupported:
                return rpc::gimbal::GimbalResult_Result_RESULT_UNSUPPORTED;
            case mavsdk::Gimbal::Result::NoSystem:
                return rpc::gimbal::GimbalResult_Result_RESULT_NO_SYSTEM;
        }
    }

    static mavsdk::Gimbal::Result
    translateFromRpcResult(const rpc::gimbal::GimbalResult::Result result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case rpc::gimbal::GimbalResult_Result_RESULT_UNKNOWN:
                return mavsdk::Gimbal::Result::Unknown;
            case rpc::gimbal::GimbalResult_Result_RESULT_SUCCESS:
                return mavsdk::Gimbal::Result::Success;
            case rpc::gimbal::GimbalResult_Result_RESULT_ERROR:
                return mavsdk::Gimbal::Result::Error;
            case rpc::gimbal::GimbalResult_Result_RESULT_TIMEOUT:
                return mavsdk::Gimbal::Result::Timeout;
            case rpc::gimbal::GimbalResult_Result_RESULT_UNSUPPORTED:
                return mavsdk::Gimbal::Result::Unsupported;
            case rpc::gimbal::GimbalResult_Result_RESULT_NO_SYSTEM:
                return mavsdk::Gimbal::Result::NoSystem;
        }
    }

    grpc::Status SetAngles(
        grpc::ServerContext* /* context */,
        const rpc::gimbal::SetAnglesRequest* request,
        rpc::gimbal::SetAnglesResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Gimbal::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "SetAngles sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->set_angles(
            request->pitch_deg(), request->yaw_deg(), request->roll_deg());

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    grpc::Status SetPitchAndYaw(
        grpc::ServerContext* /* context */,
        const rpc::gimbal::SetPitchAndYawRequest* request,
        rpc::gimbal::SetPitchAndYawResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Gimbal::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "SetPitchAndYaw sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->set_pitch_and_yaw(
            request->pitch_deg(), request->yaw_deg());

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    grpc::Status SetPitchRateAndYawRate(
        grpc::ServerContext* /* context */,
        const rpc::gimbal::SetPitchRateAndYawRateRequest* request,
        rpc::gimbal::SetPitchRateAndYawRateResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Gimbal::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "SetPitchRateAndYawRate sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->set_pitch_rate_and_yaw_rate(
            request->pitch_rate_deg_s(), request->yaw_rate_deg_s());

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    grpc::Status SetMode(
        grpc::ServerContext* /* context */,
        const rpc::gimbal::SetModeRequest* request,
        rpc::gimbal::SetModeResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Gimbal::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "SetMode sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->set_mode(
            translateFromRpcGimbalMode(request->gimbal_mode()));

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    grpc::Status SetRoiLocation(
        grpc::ServerContext* /* context */,
        const rpc::gimbal::SetRoiLocationRequest* request,
        rpc::gimbal::SetRoiLocationResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Gimbal::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "SetRoiLocation sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->set_roi_location(
            request->latitude_deg(), request->longitude_deg(), request->altitude_m());

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    grpc::Status TakeControl(
        grpc::ServerContext* /* context */,
        const rpc::gimbal::TakeControlRequest* request,
        rpc::gimbal::TakeControlResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Gimbal::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "TakeControl sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->take_control(
            translateFromRpcControlMode(request->control_mode()));

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    grpc::Status ReleaseControl(
        grpc::ServerContext* /* context */,
        const rpc::gimbal::ReleaseControlRequest* /* request */,
        rpc::gimbal::ReleaseControlResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Gimbal::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->release_control();

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    grpc::Status SubscribeControl(
        grpc::ServerContext* /* context */,
        const mavsdk::rpc::gimbal::SubscribeControlRequest* /* request */,
        grpc::ServerWriter<rpc::gimbal::ControlResponse>* writer) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            return grpc::Status::OK;
        }

        auto stream_closed_promise = std::make_shared<std::promise<void>>();
        auto stream_closed_future = stream_closed_promise->get_future();
        register_stream_stop_promise(stream_closed_promise);

        auto is_finished = std::make_shared<bool>(false);
        auto subscribe_mutex = std::make_shared<std::mutex>();

        const mavsdk::Gimbal::ControlHandle handle = _lazy_plugin.maybe_plugin()->subscribe_control(
            [this, &writer, &stream_closed_promise, is_finished, subscribe_mutex, &handle](
                const mavsdk::Gimbal::ControlStatus control) {
                rpc::gimbal::ControlResponse rpc_response;

                rpc_response.set_allocated_control_status(
                    translateToRpcControlStatus(control).release());

                std::unique_lock<std::mutex> lock(*subscribe_mutex);
                if (!*is_finished && !writer->Write(rpc_response)) {
                    _lazy_plugin.maybe_plugin()->unsubscribe_control(handle);

                    *is_finished = true;
                    unregister_stream_stop_promise(stream_closed_promise);
                    stream_closed_promise->set_value();
                }
            });

        stream_closed_future.wait();
        std::unique_lock<std::mutex> lock(*subscribe_mutex);
        *is_finished = true;

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