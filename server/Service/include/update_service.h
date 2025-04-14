#ifndef UPDATE_SERVICE_H
#define UPDATE_SERVICE_H

#include <efficio-rpc-proto/efficio.grpc.pb.h>
#include <efficio-rpc-proto/efficio.pb.h>
#include <grpc++/grpc++.h>
#include <model-proto/model.pb.h>
#include "common_server_call.h"

using grpc::ServerContext;
using grpc::ServerAsyncResponseWriter;

using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;
using Efficio_proto::GetProjectRequest;
using Efficio_proto::GetProjectResponse;
using Efficio_proto::Update;
using Efficio_proto::CreateNoteRequest;

class UpdateService final {
    Update::AsyncService service_;
    ServerContext ctx_;
    ServerCompletionQueue *cq_;

public:

    explicit UpdateService(ServerCompletionQueue* cq);
    class GetNoteServerCall final : public CommonServerCall {
        GetNoteRequest request_;
        ServerAsyncResponseWriter<GetNoteResponse> responder_;
        Update::AsyncService *service_;

    public:
        explicit GetNoteServerCall(Update::AsyncService *service, ServerCompletionQueue *cq);
        void Proceed(bool ok) override;
    };

    class GetProjectServerCall final : public CommonServerCall {
        GetProjectRequest request_;
        GetProjectResponse response_;
        ServerAsyncResponseWriter<GetProjectResponse> responder_;
        Update::AsyncService *service_;
    public:
        explicit GetProjectServerCall(Update::AsyncService* service, ServerCompletionQueue *cq);
        void Proceed(bool) override;
    };

    class TryJoinProjectServerCall;
    class CreateProjectServerCall;

    class CreateNoteServerCall final : public CommonServerCall {
        CreateNoteRequest request_;
        ServerAsyncResponseWriter<CreateNoteRequest> responder_;
        UpdateService &service_;
    public:
        explicit CreateNoteServerCall(UpdateService& service, ServerCompletionQueue *cq);
        void Proceed(bool) override;
    };

    Update::AsyncService& get_service();
    void run();

};

#endif //UPDATE_SERVICE_H
