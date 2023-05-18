// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/follow_me/follow_me.proto)

#include "follow_me/follow_me.grpc.pb.h"
#include "plugins/follow_me/follow_me.h"

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


template<typename FollowMe = FollowMe, typename LazyPlugin = LazyPlugin<FollowMe>>

class FollowMeServiceImpl final : public rpc::follow_me::FollowMeService::Service {
public:

    FollowMeServiceImpl(LazyPlugin& lazy_plugin) : _lazy_plugin(lazy_plugin) {}



    template<typename ResponseType>
    void fillResponseWithResult(ResponseType* response, mavsdk::FollowMe::Result& result) const
    {
        auto rpc_result = translateToRpcResult(result);

        auto* rpc_follow_me_result = new rpc::follow_me::FollowMeResult();
        rpc_follow_me_result->set_result(rpc_result);
        std::stringstream ss;
        ss << result;
        rpc_follow_me_result->set_result_str(ss.str());

        response->set_allocated_follow_me_result(rpc_follow_me_result);
    }



    static rpc::follow_me::Config::FollowAltitudeMode translateToRpcFollowAltitudeMode(const mavsdk::FollowMe::Config::FollowAltitudeMode& follow_altitude_mode)
    {
        switch (follow_altitude_mode) {
            default:
                LogErr() << "Unknown follow_altitude_mode enum value: " << static_cast<int>(follow_altitude_mode);
            // FALLTHROUGH
            case mavsdk::FollowMe::Config::FollowAltitudeMode::Constant:
                return rpc::follow_me::Config_FollowAltitudeMode_FOLLOW_ALTITUDE_MODE_CONSTANT;
            case mavsdk::FollowMe::Config::FollowAltitudeMode::Terrain:
                return rpc::follow_me::Config_FollowAltitudeMode_FOLLOW_ALTITUDE_MODE_TERRAIN;
            case mavsdk::FollowMe::Config::FollowAltitudeMode::TargetGps:
                return rpc::follow_me::Config_FollowAltitudeMode_FOLLOW_ALTITUDE_MODE_TARGET_GPS;
        }
    }

    static mavsdk::FollowMe::Config::FollowAltitudeMode translateFromRpcFollowAltitudeMode(const rpc::follow_me::Config::FollowAltitudeMode follow_altitude_mode)
    {
        switch (follow_altitude_mode) {
            default:
                LogErr() << "Unknown follow_altitude_mode enum value: " << static_cast<int>(follow_altitude_mode);
            // FALLTHROUGH
            case rpc::follow_me::Config_FollowAltitudeMode_FOLLOW_ALTITUDE_MODE_CONSTANT:
                return mavsdk::FollowMe::Config::FollowAltitudeMode::Constant;
            case rpc::follow_me::Config_FollowAltitudeMode_FOLLOW_ALTITUDE_MODE_TERRAIN:
                return mavsdk::FollowMe::Config::FollowAltitudeMode::Terrain;
            case rpc::follow_me::Config_FollowAltitudeMode_FOLLOW_ALTITUDE_MODE_TARGET_GPS:
                return mavsdk::FollowMe::Config::FollowAltitudeMode::TargetGps;
        }
    }


    static std::unique_ptr<rpc::follow_me::Config> translateToRpcConfig(const mavsdk::FollowMe::Config &config)
    {
        auto rpc_obj = std::make_unique<rpc::follow_me::Config>();


            
        rpc_obj->set_follow_height_m(config.follow_height_m);
            
        
            
        rpc_obj->set_follow_distance_m(config.follow_distance_m);
            
        
            
        rpc_obj->set_responsiveness(config.responsiveness);
            
        
            
                
        rpc_obj->set_altitude_mode(translateToRpcFollowAltitudeMode(config.altitude_mode));
                
            
        
            
        rpc_obj->set_max_tangential_vel_m_s(config.max_tangential_vel_m_s);
            
        
            
        rpc_obj->set_follow_angle_deg(config.follow_angle_deg);
            
        

        return rpc_obj;
    }

    static mavsdk::FollowMe::Config translateFromRpcConfig(const rpc::follow_me::Config& config)
    {
        mavsdk::FollowMe::Config obj;


            
        obj.follow_height_m = config.follow_height_m();
            
        
            
        obj.follow_distance_m = config.follow_distance_m();
            
        
            
        obj.responsiveness = config.responsiveness();
            
        
            
        obj.altitude_mode = translateFromRpcFollowAltitudeMode(config.altitude_mode());
            
        
            
        obj.max_tangential_vel_m_s = config.max_tangential_vel_m_s();
            
        
            
        obj.follow_angle_deg = config.follow_angle_deg();
            
        
        return obj;
    }





    static std::unique_ptr<rpc::follow_me::TargetLocation> translateToRpcTargetLocation(const mavsdk::FollowMe::TargetLocation &target_location)
    {
        auto rpc_obj = std::make_unique<rpc::follow_me::TargetLocation>();


            
        rpc_obj->set_latitude_deg(target_location.latitude_deg);
            
        
            
        rpc_obj->set_longitude_deg(target_location.longitude_deg);
            
        
            
        rpc_obj->set_absolute_altitude_m(target_location.absolute_altitude_m);
            
        
            
        rpc_obj->set_velocity_x_m_s(target_location.velocity_x_m_s);
            
        
            
        rpc_obj->set_velocity_y_m_s(target_location.velocity_y_m_s);
            
        
            
        rpc_obj->set_velocity_z_m_s(target_location.velocity_z_m_s);
            
        

        return rpc_obj;
    }

    static mavsdk::FollowMe::TargetLocation translateFromRpcTargetLocation(const rpc::follow_me::TargetLocation& target_location)
    {
        mavsdk::FollowMe::TargetLocation obj;


            
        obj.latitude_deg = target_location.latitude_deg();
            
        
            
        obj.longitude_deg = target_location.longitude_deg();
            
        
            
        obj.absolute_altitude_m = target_location.absolute_altitude_m();
            
        
            
        obj.velocity_x_m_s = target_location.velocity_x_m_s();
            
        
            
        obj.velocity_y_m_s = target_location.velocity_y_m_s();
            
        
            
        obj.velocity_z_m_s = target_location.velocity_z_m_s();
            
        
        return obj;
    }




    static rpc::follow_me::FollowMeResult::Result translateToRpcResult(const mavsdk::FollowMe::Result& result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case mavsdk::FollowMe::Result::Unknown:
                return rpc::follow_me::FollowMeResult_Result_RESULT_UNKNOWN;
            case mavsdk::FollowMe::Result::Success:
                return rpc::follow_me::FollowMeResult_Result_RESULT_SUCCESS;
            case mavsdk::FollowMe::Result::NoSystem:
                return rpc::follow_me::FollowMeResult_Result_RESULT_NO_SYSTEM;
            case mavsdk::FollowMe::Result::ConnectionError:
                return rpc::follow_me::FollowMeResult_Result_RESULT_CONNECTION_ERROR;
            case mavsdk::FollowMe::Result::Busy:
                return rpc::follow_me::FollowMeResult_Result_RESULT_BUSY;
            case mavsdk::FollowMe::Result::CommandDenied:
                return rpc::follow_me::FollowMeResult_Result_RESULT_COMMAND_DENIED;
            case mavsdk::FollowMe::Result::Timeout:
                return rpc::follow_me::FollowMeResult_Result_RESULT_TIMEOUT;
            case mavsdk::FollowMe::Result::NotActive:
                return rpc::follow_me::FollowMeResult_Result_RESULT_NOT_ACTIVE;
            case mavsdk::FollowMe::Result::SetConfigFailed:
                return rpc::follow_me::FollowMeResult_Result_RESULT_SET_CONFIG_FAILED;
        }
    }

    static mavsdk::FollowMe::Result translateFromRpcResult(const rpc::follow_me::FollowMeResult::Result result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case rpc::follow_me::FollowMeResult_Result_RESULT_UNKNOWN:
                return mavsdk::FollowMe::Result::Unknown;
            case rpc::follow_me::FollowMeResult_Result_RESULT_SUCCESS:
                return mavsdk::FollowMe::Result::Success;
            case rpc::follow_me::FollowMeResult_Result_RESULT_NO_SYSTEM:
                return mavsdk::FollowMe::Result::NoSystem;
            case rpc::follow_me::FollowMeResult_Result_RESULT_CONNECTION_ERROR:
                return mavsdk::FollowMe::Result::ConnectionError;
            case rpc::follow_me::FollowMeResult_Result_RESULT_BUSY:
                return mavsdk::FollowMe::Result::Busy;
            case rpc::follow_me::FollowMeResult_Result_RESULT_COMMAND_DENIED:
                return mavsdk::FollowMe::Result::CommandDenied;
            case rpc::follow_me::FollowMeResult_Result_RESULT_TIMEOUT:
                return mavsdk::FollowMe::Result::Timeout;
            case rpc::follow_me::FollowMeResult_Result_RESULT_NOT_ACTIVE:
                return mavsdk::FollowMe::Result::NotActive;
            case rpc::follow_me::FollowMeResult_Result_RESULT_SET_CONFIG_FAILED:
                return mavsdk::FollowMe::Result::SetConfigFailed;
        }
    }




    grpc::Status GetConfig(
        grpc::ServerContext* /* context */,
        const rpc::follow_me::GetConfigRequest* /* request */,
        rpc::follow_me::GetConfigResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            
            return grpc::Status::OK;
        }

        

        auto result = _lazy_plugin.maybe_plugin()->get_config();

        if (response != nullptr) {
            
            
            response->set_allocated_config(translateToRpcConfig(result).release());
            
        }


        return grpc::Status::OK;
    }

    grpc::Status SetConfig(
        grpc::ServerContext* /* context */,
        const rpc::follow_me::SetConfigRequest* request,
        rpc::follow_me::SetConfigResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            
            if (response != nullptr) {
                auto result = mavsdk::FollowMe::Result::NoSystem;
                fillResponseWithResult(response, result);
            }
            
            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "SetConfig sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }
            
        
        auto result = _lazy_plugin.maybe_plugin()->set_config(translateFromRpcConfig(request->config()));
        

        
        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }
        

        return grpc::Status::OK;
    }

    grpc::Status IsActive(
        grpc::ServerContext* /* context */,
        const rpc::follow_me::IsActiveRequest* /* request */,
        rpc::follow_me::IsActiveResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            
            return grpc::Status::OK;
        }

        

        auto result = _lazy_plugin.maybe_plugin()->is_active();

        if (response != nullptr) {
            
            
            response->set_is_active(result);
            
        }


        return grpc::Status::OK;
    }

    grpc::Status SetTargetLocation(
        grpc::ServerContext* /* context */,
        const rpc::follow_me::SetTargetLocationRequest* request,
        rpc::follow_me::SetTargetLocationResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            
            if (response != nullptr) {
                auto result = mavsdk::FollowMe::Result::NoSystem;
                fillResponseWithResult(response, result);
            }
            
            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "SetTargetLocation sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }
            
        
        auto result = _lazy_plugin.maybe_plugin()->set_target_location(translateFromRpcTargetLocation(request->location()));
        

        
        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }
        

        return grpc::Status::OK;
    }

    grpc::Status GetLastLocation(
        grpc::ServerContext* /* context */,
        const rpc::follow_me::GetLastLocationRequest* /* request */,
        rpc::follow_me::GetLastLocationResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            
            return grpc::Status::OK;
        }

        

        auto result = _lazy_plugin.maybe_plugin()->get_last_location();

        if (response != nullptr) {
            
            
            response->set_allocated_location(translateToRpcTargetLocation(result).release());
            
        }


        return grpc::Status::OK;
    }

    grpc::Status Start(
        grpc::ServerContext* /* context */,
        const rpc::follow_me::StartRequest* /* request */,
        rpc::follow_me::StartResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            
            if (response != nullptr) {
                auto result = mavsdk::FollowMe::Result::NoSystem;
                fillResponseWithResult(response, result);
            }
            
            return grpc::Status::OK;
        }

        
        auto result = _lazy_plugin.maybe_plugin()->start();
        

        
        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }
        

        return grpc::Status::OK;
    }

    grpc::Status Stop(
        grpc::ServerContext* /* context */,
        const rpc::follow_me::StopRequest* /* request */,
        rpc::follow_me::StopResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            
            if (response != nullptr) {
                auto result = mavsdk::FollowMe::Result::NoSystem;
                fillResponseWithResult(response, result);
            }
            
            return grpc::Status::OK;
        }

        
        auto result = _lazy_plugin.maybe_plugin()->stop();
        

        
        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }
        

        return grpc::Status::OK;
    }


    void stop() {
        _stopped.store(true);
        for (auto& prom : _stream_stop_promises) {
            if (auto handle = prom.lock()) {
                handle->set_value();
            }
        }
    }

private:
    void register_stream_stop_promise(std::weak_ptr<std::promise<void>> prom) {
        // If we have already stopped, set promise immediately and don't add it to list.
        if (_stopped.load()) {
            if (auto handle = prom.lock()) {
                handle->set_value();
            }
        } else {
            _stream_stop_promises.push_back(prom);
        }
    }

    void unregister_stream_stop_promise(std::shared_ptr<std::promise<void>> prom) {
        for (auto it = _stream_stop_promises.begin(); it != _stream_stop_promises.end(); /* ++it */) {
            if (it->lock() == prom) {
                it = _stream_stop_promises.erase(it);
            } else {
                ++it;
            }
        }
    }


    LazyPlugin& _lazy_plugin;

    std::atomic<bool> _stopped{false};
    std::vector<std::weak_ptr<std::promise<void>>> _stream_stop_promises {};
};

} // namespace mavsdk_server
} // namespace mavsdk