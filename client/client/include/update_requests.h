#ifndef UPDATE_REQUESTS_H
#define UPDATE_REQUESTS_H

#include <efficio-rpc-proto/efficio.grpc.pb.h>
#include <efficio-rpc-proto/efficio.pb.h>
#include <grpc++/grpc++.h>
#include "common_client_call.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::CompletionQueue;

using Efficio_proto::Update;
using Efficio_proto::Note;
using Efficio_proto::Project;
using Efficio_proto::Storage;
using Efficio_proto::GetProjectRequest;
using Efficio_proto::GetProjectResponse;
using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;

class UpdateRequests {
    public:



    class GetProjectClientCall final : public CommonClientCall {
        GetProjectResponse response;
        std::unique_ptr<ClientAsyncResponseReader<GetProjectResponse>> response_reader;
        public:
        void Proceed(bool ok) override;

        GetProjectClientCall(const GetProjectRequest& request,
        CompletionQueue* cq_,
        std::unique_ptr<Update::Stub>& stub_);
    };


    class GetNoteClientCall;
    class CreateNoteClientCall;
    class CreateProjectClientCall;
    class TryJoinProjectClientCall;

    bool get_note(Note *note);
    bool get_project(Project *project);
    bool create_note(Note *note);
    bool create_project(Project *project);
    bool try_join_project(Project *project);



    explicit UpdateRequests(std::shared_ptr<Channel> channel, CompletionQueue *cq):
        stub_(Update::NewStub(channel)), cq_(cq) {};
    private:
    CompletionQueue* cq_;
    std::unique_ptr<Update::Stub> stub_;


};


#endif //UPDATE_REQUESTS_H
