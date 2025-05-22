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
using Efficio_proto::CreateProjectRequest;
using Efficio_proto::CreateProjectResponse;
using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;
using Efficio_proto::GetProjectRequest;
using Efficio_proto::GetProjectResponse;
using Efficio_proto::TryJoinProjectRequest;
using Efficio_proto::TryJoinProjectResponse;
using Efficio_proto::TryLeaveProjectRequest;
using Efficio_proto::TryLeaveProjectResponse;
using Efficio_proto::Update;
using Efficio_proto::UpdateNoteRequest;
using Efficio_proto::UpdateNoteResponse;

class UpdateService final {
    Update::AsyncService service_;
    ServerContext ctx_;
    std::unique_ptr<ServerCompletionQueue> cq_;
    std::unique_ptr<grpc::Server> server_;

public:
    UpdateService(ServerCompletionQueue *cq);

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
        GetProjectRequest request_;
        GetProjectResponse response_;
        ServerAsyncResponseWriter<GetProjectResponse> responder_;
        Update::AsyncService *service_;

    public:
        explicit GetProjectServerCall(
            Update::AsyncService *service,
            ServerCompletionQueue *cq
        );
        void Proceed(bool) override;
    };

    class CreateProjectServerCall : public CommonServerCall {
        CreateProjectRequest request_;
        CreateProjectResponse response_;
        ServerAsyncResponseWriter<CreateProjectResponse> responder_;
        Update::AsyncService *service_;

    public:
        explicit CreateProjectServerCall(
            Update::AsyncService *service,
            ServerCompletionQueue *cq
        );
        void Proceed(bool) override;
    };

    class TryJoinProjectServerCall : public CommonServerCall {
        TryJoinProjectRequest request_;
        TryJoinProjectResponse response_;
        ServerAsyncResponseWriter<TryJoinProjectResponse> responder_;
        Update::AsyncService *service_;

    public:
        explicit TryJoinProjectServerCall(
            Update::AsyncService *service,
            ServerCompletionQueue *cq
        );
        void Proceed(bool) override;
    };

    class TryLeaveProjectServerCall : public CommonServerCall {
        TryLeaveProjectRequest request_;
        TryLeaveProjectResponse response_;
        ServerAsyncResponseWriter<TryLeaveProjectResponse> responder_;
        Update::AsyncService *service_;

    public:
        explicit TryLeaveProjectServerCall(
            Update::AsyncService *service,
            ServerCompletionQueue *cq
        );
        void Proceed(bool) override;
    };

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

    void run();
};

#endif  // UPDATE_SERVICE_H
