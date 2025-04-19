#ifndef UPDATE_REQUESTS_H
#define UPDATE_REQUESTS_H

#include <efficio-rpc-proto/efficio.grpc.pb.h>
#include <efficio-rpc-proto/efficio.pb.h>
#include <grpc++/grpc++.h>
#include "common_client_call.h"

using grpc::Channel;

using Efficio_proto::Update;
using Efficio_proto::Note;
using Efficio_proto::Project;
using Efficio_proto::Storage;

using Efficio_proto::GetNoteResponse;
using Efficio_proto::GetNoteRequest;
using Efficio_proto::CreateNoteResponse;
using Efficio_proto::CreateNoteRequest;

class UpdateRequests {
public:
    class GetNoteClientCall final : public CommonClientCall {
        GetNoteResponse reply_;
        std::unique_ptr<grpc::ClientAsyncResponseReader<GetNoteResponse>>
            responder_;

    public:
        GetNoteClientCall(
            const GetNoteRequest &request,
            grpc::CompletionQueue *cq,
            const std::unique_ptr<Update::Stub> &stub
        );
        void Proceed(bool ok = true) override;
        GetNoteResponse get_reply();
    };

    class GetProjectClientCall;

    class CreateNoteClientCall final : public CommonClientCall {
        CreateNoteResponse reply_;
        std::unique_ptr<grpc::ClientAsyncResponseReader<CreateNoteResponse>>
            responder_;

    public:
        CreateNoteClientCall(
            const CreateNoteRequest &request,
            grpc::CompletionQueue *cq,
            const std::unique_ptr<Update::Stub> &stub
        );
        void Proceed(bool ok = true) override;
        CreateNoteResponse get_reply();
    };

    class CreateProjectClientCall;
    class TryJoinProjectClientCall;

    bool fetch_note(Note *note) const;
    bool get_project(Project *project);
    bool create_note(Note *note) const;
    bool create_project(Project *project);
    bool try_join_project(Project *project);

    explicit UpdateRequests(
        const std::shared_ptr<Channel> &channel,
        grpc::CompletionQueue *cq
    )
        : cq_(cq), stub_(Update::NewStub(channel)) {};

private:
    grpc::CompletionQueue *cq_;
    std::unique_ptr<Update::Stub> stub_;
};


#endif //UPDATE_REQUESTS_H
