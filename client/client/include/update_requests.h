#ifndef UPDATE_REQUESTS_H
#define UPDATE_REQUESTS_H

#include <efficio-rpc-proto/efficio.grpc.pb.h>
#include <efficio-rpc-proto/efficio.pb.h>
#include <grpc++/grpc++.h>
#include "common_client_call.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::CompletionQueue;

using Efficio_proto::Note;
using Efficio_proto::Project;
using Efficio_proto::Storage;
using Efficio_proto::Update;
using Efficio_proto::User;

using Efficio_proto::CreateNoteRequest;
using Efficio_proto::CreateNoteResponse;
using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;
using Efficio_proto::UpdateNoteRequest;
using Efficio_proto::UpdateNoteResponse;

class UpdateRequests {
public:
    class UpdateNoteClientCall final : public CommonClientCall {
        UpdateNoteResponse reply_;
        std::unique_ptr<grpc::ClientAsyncResponseReader<UpdateNoteResponse>>
            responder_;

    public:
        UpdateNoteClientCall(
            const UpdateNoteRequest &request,
            grpc::CompletionQueue *cq,
            const std::unique_ptr<Update::Stub> &stub
        );
        void Proceed(bool ok) override;
        UpdateNoteResponse get_reply();
    };

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
        void Proceed(bool ok) override;
        GetNoteResponse get_reply();
    };

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
        void Proceed(bool ok) override;
        CreateNoteResponse get_reply();
    };

    bool try_update_note(Note *note) const;
    bool try_fetch_note(Note *note) const;
    bool try_create_note(Note *note, const std::string &project_code) const;
    bool get_note(Note *note);
    std::vector<std::string> get_project_members(
        const std::string &project_code
    ) const;
    bool create_note(Note *note);

    bool get_project(Project &project, const std::string &code);
    bool create_project(
        Project &project,
        const std::string &project_title,
        const User &user
    );
    bool try_leave_project(const std::string &code, const User &user);
    bool try_join_project(
        Project &project,
        const std::string &code,
        const User &user
    );

    explicit UpdateRequests(
        std::shared_ptr<Channel> channel,
        const std::shared_ptr<CompletionQueue>& cq
    )
        : stub_(Update::NewStub(channel)), cq_(cq) {
    }

private:
    std::shared_ptr<CompletionQueue> cq_;
    std::unique_ptr<Update::Stub> stub_;
};

#endif  // UPDATE_REQUESTS_H
