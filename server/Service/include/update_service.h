#ifndef UPDATE_SERVICE_H
#define UPDATE_SERVICE_H

#include <efficio-rpc-proto/efficio.grpc.pb.h>
#include <efficio-rpc-proto/efficio.pb.h>
#include <grpc++/grpc++.h>
#include "common_server_call.h"

using grpc::ServerAsyncResponseWriter;
using grpc::ServerContext;

using Efficio_proto::CreateNoteRequest;
using Efficio_proto::CreateNoteResponse;
using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;
using Efficio_proto::Update;
using Efficio_proto::UpdateNoteRequest;
using Efficio_proto::UpdateNoteResponse;

class UpdateService final {
    Update::AsyncService service_;
    ServerContext ctx_;
    std::unique_ptr<ServerCompletionQueue> cq_;
    std::unique_ptr<grpc::Server> server_;

public:
    class UpdateNoteServerCall final : public CommonServerCall {
        UpdateNoteRequest request_;
        ServerAsyncResponseWriter<UpdateNoteResponse> responder_;
        UpdateService &service_;

    public:
        explicit UpdateNoteServerCall(
            UpdateService &service,
            ServerCompletionQueue *cq
        );
        void Proceed(bool ok) override;
    };

    class GetNoteServerCall final : public CommonServerCall {
        GetNoteRequest request_;
        ServerAsyncResponseWriter<GetNoteResponse> responder_;
        UpdateService &service_;

    public:
        explicit GetNoteServerCall(
            UpdateService &service,
            ServerCompletionQueue *cq
        );
        void Proceed(bool ok) override;
    };

    class GetProjectServerCall final : public CommonServerCall {
    public:
        explicit GetProjectServerCall(UpdateService &service);
        void Proceed(bool ok) override;

        // TODO: finish this call
    };

    class TryJoinProjectServerCall;
    class CreateProjectServerCall;

    class CreateNoteServerCall final : public CommonServerCall {
        CreateNoteRequest request_;
        ServerAsyncResponseWriter<CreateNoteResponse> responder_;
        UpdateService &service_;

    public:
        explicit CreateNoteServerCall(
            UpdateService &service,
            ServerCompletionQueue *cq
        );
        void Proceed(bool ok) override;
    };

    Update::AsyncService &get_service();
};

#endif  // UPDATE_SERVICE_H
