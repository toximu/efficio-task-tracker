#pragma once

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
        std::unique_ptr<ClientAsyncResponseReader<UpdateNoteResponse>>
            responder_;

    public:
        UpdateNoteClientCall(
            const UpdateNoteRequest &request,
            CompletionQueue *cq,
            const std::unique_ptr<Update::Stub> &stub
        );
        void Proceed(bool ok) override;
        UpdateNoteResponse get_reply();
    };

    class GetNoteClientCall final : public CommonClientCall {
        GetNoteResponse reply_;
        std::unique_ptr<ClientAsyncResponseReader<GetNoteResponse>> responder_;

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
        std::unique_ptr<ClientAsyncResponseReader<CreateNoteResponse>>
            responder_;

    public:
        CreateNoteClientCall(
            const CreateNoteRequest &request,
            CompletionQueue *cq,
            const std::unique_ptr<Update::Stub> &stub
        );
        void Proceed(bool ok) override;
        CreateNoteResponse get_reply();
    };

    bool try_update_note(Note *note) const;
    bool try_fetch_note(Note *note) const;
    bool try_create_note(Note *note, const std::string &project_code) const;
    std::vector<std::string> get_project_members(
        const std::string &project_code
    ) const;

    bool get_project(Project &project, const std::string &code) const;
    bool create_project(
        Project &project,
        const std::string &project_title,
        const User &user
    ) const;
    bool try_leave_project(const std::string &code, const User &user) const;
    bool try_join_project(
        Project &project,
        const std::string &code,
        const User &user
    ) const;

    explicit UpdateRequests(
        const std::shared_ptr<Channel> &channel,
        const std::shared_ptr<CompletionQueue> &cq
    )
        : cq_(cq), stub_(Update::NewStub(channel)) {
    }

private:
    std::shared_ptr<CompletionQueue> cq_;
    std::unique_ptr<Update::Stub> stub_;
};
