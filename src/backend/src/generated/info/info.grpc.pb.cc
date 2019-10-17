// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: info/info.proto

#include "info/info.pb.h"
#include "info/info.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace mavsdk {
namespace rpc {
namespace info {

static const char* InfoService_method_names[] = {
  "/mavsdk.rpc.info.InfoService/GetVersion",
};

std::unique_ptr< InfoService::Stub> InfoService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< InfoService::Stub> stub(new InfoService::Stub(channel));
  return stub;
}

InfoService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_GetVersion_(InfoService_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status InfoService::Stub::GetVersion(::grpc::ClientContext* context, const ::mavsdk::rpc::info::GetVersionRequest& request, ::mavsdk::rpc::info::GetVersionResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetVersion_, context, request, response);
}

void InfoService::Stub::experimental_async::GetVersion(::grpc::ClientContext* context, const ::mavsdk::rpc::info::GetVersionRequest* request, ::mavsdk::rpc::info::GetVersionResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetVersion_, context, request, response, std::move(f));
}

void InfoService::Stub::experimental_async::GetVersion(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::mavsdk::rpc::info::GetVersionResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetVersion_, context, request, response, std::move(f));
}

void InfoService::Stub::experimental_async::GetVersion(::grpc::ClientContext* context, const ::mavsdk::rpc::info::GetVersionRequest* request, ::mavsdk::rpc::info::GetVersionResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_GetVersion_, context, request, response, reactor);
}

void InfoService::Stub::experimental_async::GetVersion(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::mavsdk::rpc::info::GetVersionResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_GetVersion_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::mavsdk::rpc::info::GetVersionResponse>* InfoService::Stub::AsyncGetVersionRaw(::grpc::ClientContext* context, const ::mavsdk::rpc::info::GetVersionRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::mavsdk::rpc::info::GetVersionResponse>::Create(channel_.get(), cq, rpcmethod_GetVersion_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::mavsdk::rpc::info::GetVersionResponse>* InfoService::Stub::PrepareAsyncGetVersionRaw(::grpc::ClientContext* context, const ::mavsdk::rpc::info::GetVersionRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::mavsdk::rpc::info::GetVersionResponse>::Create(channel_.get(), cq, rpcmethod_GetVersion_, context, request, false);
}

InfoService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      InfoService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< InfoService::Service, ::mavsdk::rpc::info::GetVersionRequest, ::mavsdk::rpc::info::GetVersionResponse>(
          std::mem_fn(&InfoService::Service::GetVersion), this)));
}

InfoService::Service::~Service() {
}

::grpc::Status InfoService::Service::GetVersion(::grpc::ServerContext* context, const ::mavsdk::rpc::info::GetVersionRequest* request, ::mavsdk::rpc::info::GetVersionResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace mavsdk
}  // namespace rpc
}  // namespace info

