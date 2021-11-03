// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/camera_trigger_server/camera_trigger_server.proto)

#include "camera_trigger_server/camera_trigger_server.grpc.pb.h"
#include "plugins/camera_trigger_server/camera_trigger_server.h"

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

template<typename CameraTriggerServer = CameraTriggerServer, typename LazyPlugin = LazyPlugin<CameraTriggerServer>>
class CameraTriggerServerServiceImpl final : public rpc::camera_trigger_server::CameraTriggerServerService::Service {
public:
    CameraTriggerServerServiceImpl(LazyPlugin& lazy_plugin) : _lazy_plugin(lazy_plugin) {}


    template<typename ResponseType>
    void fillResponseWithResult(ResponseType* response, mavsdk::CameraTriggerServer::Result& result) const
    {
        auto rpc_result = translateToRpcResult(result);

        auto* rpc_camera_trigger_server_result = new rpc::camera_trigger_server::CameraTriggerServerResult();
        rpc_camera_trigger_server_result->set_result(rpc_result);
        std::stringstream ss;
        ss << result;
        rpc_camera_trigger_server_result->set_result_str(ss.str());

        response->set_allocated_camera_trigger_server_result(rpc_camera_trigger_server_result);
    }



    static rpc::camera_trigger_server::CameraTriggerServerResult::Result translateToRpcResult(const mavsdk::CameraTriggerServer::Result& result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case mavsdk::CameraTriggerServer::Result::Unknown:
                return rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_UNKNOWN;
            case mavsdk::CameraTriggerServer::Result::Success:
                return rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_SUCCESS;
            case mavsdk::CameraTriggerServer::Result::NoSystem:
                return rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_NO_SYSTEM;
            case mavsdk::CameraTriggerServer::Result::ConnectionError:
                return rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_CONNECTION_ERROR;
            case mavsdk::CameraTriggerServer::Result::Busy:
                return rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_BUSY;
            case mavsdk::CameraTriggerServer::Result::CommandDenied:
                return rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_COMMAND_DENIED;
            case mavsdk::CameraTriggerServer::Result::Timeout:
                return rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_TIMEOUT;
            case mavsdk::CameraTriggerServer::Result::Unsupported:
                return rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_UNSUPPORTED;
        }
    }

    static mavsdk::CameraTriggerServer::Result translateFromRpcResult(const rpc::camera_trigger_server::CameraTriggerServerResult::Result result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_UNKNOWN:
                return mavsdk::CameraTriggerServer::Result::Unknown;
            case rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_SUCCESS:
                return mavsdk::CameraTriggerServer::Result::Success;
            case rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_NO_SYSTEM:
                return mavsdk::CameraTriggerServer::Result::NoSystem;
            case rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_CONNECTION_ERROR:
                return mavsdk::CameraTriggerServer::Result::ConnectionError;
            case rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_BUSY:
                return mavsdk::CameraTriggerServer::Result::Busy;
            case rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_COMMAND_DENIED:
                return mavsdk::CameraTriggerServer::Result::CommandDenied;
            case rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_TIMEOUT:
                return mavsdk::CameraTriggerServer::Result::Timeout;
            case rpc::camera_trigger_server::CameraTriggerServerResult_Result_RESULT_UNSUPPORTED:
                return mavsdk::CameraTriggerServer::Result::Unsupported;
        }
    }




    grpc::Status SubscribeCapture(grpc::ServerContext* /* context */, const mavsdk::rpc::camera_trigger_server::SubscribeCaptureRequest* /* request */, grpc::ServerWriter<rpc::camera_trigger_server::CaptureResponse>* writer) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            
                rpc::camera_trigger_server::CaptureResponse rpc_response;
                auto result = mavsdk::CameraTriggerServer::Result::NoSystem;
                fillResponseWithResult(&rpc_response, result);
                writer->Write(rpc_response);
            
            return grpc::Status::OK;
        }

        auto stream_closed_promise = std::make_shared<std::promise<void>>();
        auto stream_closed_future = stream_closed_promise->get_future();
        register_stream_stop_promise(stream_closed_promise);

        auto is_finished = std::make_shared<bool>(false);
        auto subscribe_mutex = std::make_shared<std::mutex>();

        _lazy_plugin.maybe_plugin()->subscribe_capture(
            [this, &writer, &stream_closed_promise, is_finished, subscribe_mutex](mavsdk::CameraTriggerServer::Result result,const uint32_t capture) {

            rpc::camera_trigger_server::CaptureResponse rpc_response;
        
            rpc_response.set_sequence_number(capture);
        

        
            auto rpc_result = translateToRpcResult(result);
            auto* rpc_camera_trigger_server_result = new rpc::camera_trigger_server::CameraTriggerServerResult();
            rpc_camera_trigger_server_result->set_result(rpc_result);
            std::stringstream ss;
            ss << result;
            rpc_camera_trigger_server_result->set_result_str(ss.str());
            rpc_response.set_allocated_camera_trigger_server_result(rpc_camera_trigger_server_result);
        

            std::unique_lock<std::mutex> lock(*subscribe_mutex);
            if (!*is_finished && !writer->Write(rpc_response)) {
                
                _lazy_plugin.maybe_plugin()->subscribe_capture(nullptr);
                
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