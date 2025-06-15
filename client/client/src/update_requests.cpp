#include "update_requests.h"
#include <common_client_call.h>
#include <efficio-rpc-proto/efficio.grpc.pb.h>
#include <efficio-rpc-proto/efficio.pb.h>
#include <grpcpp/grpcpp.h>
#include "logger.hpp"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

using Efficio_proto::CreateProjectRequest;
using Efficio_proto::CreateProjectResponse;
using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;
using Efficio_proto::GetProjectMembersRequest;
using Efficio_proto::GetProjectMembersResponse;
using Efficio_proto::GetProjectRequest;
using Efficio_proto::GetProjectResponse;
using Efficio_proto::TryJoinProjectRequest;
using Efficio_proto::TryJoinProjectResponse;
using Efficio_proto::TryLeaveProjectRequest;
using Efficio_proto::TryLeaveProjectResponse;
using Efficio_proto::Update;
using Efficio_proto::User;

bool UpdateRequests::get_project(
    Project &project,
    const std::string &code
) const {
    GetProjectRequest request;

    request.set_code(code);

    GetProjectResponse response;

    ClientContext context;

    logger << "[CLIENT(GetProjectClientCall)] : SENDING REQUEST\n";

    Status status = stub_->GetProject(&context, request, &response);

    if (status.ok() && response.has_project()) {
        logger << "[CLIENT(GetProjectClientCall)] : GOT PROJECT\n";
        project = std::move(*response.mutable_project());
        return true;
    }

    if (response.has_error_text()) {
        logger << "[CLIENT-ERROR(GetProjectClientCall)] : " +
                      response.error_text() + "\n";
    } else {
        logger << "[CLIENT-WARNING(GetProjectClientCall)] : STATUS IS NOT OK\n";
    }

    return false;
}

bool UpdateRequests::create_project(
    Project &project,
    const std::string &project_title,
    const User &user
) const {
    CreateProjectRequest request;
    request.set_project_title(project_title);
    User *copy_user = new User(user);
    request.set_allocated_user(copy_user);

    CreateProjectResponse response;

    ClientContext context;

    logger << "[CLIENT(CreateProjectClientCall)] : SENDING REQUEST\n";
    Status status = stub_->CreateProject(&context, request, &response);

    if (status.ok() && response.has_project()) {
        logger << "[CLIENT(CreateProjectClientCall)] : GOT PROJECT\n";
        project = std::move(*response.mutable_project());
        return true;
    }

    if (response.has_error_text()) {
        logger << "[CLIENT-ERROR(CreateProjectClientCall)] : " +
                      response.error_text() + "\n";
    } else {
        logger
            << "[CLIENT-WARNING(CreateProjectClientCall)] : STATUS IS NOT OK\n";
    }
    return false;
}

bool UpdateRequests::try_leave_project(
    const std::string &code,
    const User &user
) const {
    TryLeaveProjectRequest request;

    request.set_code(code);
    User *copy_user = new User(user);
    request.set_allocated_user(copy_user);

    TryLeaveProjectResponse response;
    ClientContext context;
    logger << "[CLIENT(TryLeaveProjectClientCall)] : SENDING REQUEST\n";
    Status status = stub_->TryLeaveProject(&context, request, &response);

    if (status.ok() && response.ok()) {
        logger << "[CLIENT(TryLeaveProjectClientCall)] : LEFT PROJECT\n";
        return true;
    }

    logger << "[CLIENT-ERROR(TryLeaveProjectClientCall)] : CANT LEAVE\n";
    return false;
}

bool UpdateRequests::try_join_project(
    Project &project,
    const std::string &code,
    const User &user
) const {
    TryJoinProjectRequest request;
    request.set_code(code);
    User *copy_user = new User(user);
    request.set_allocated_user(copy_user);
    TryJoinProjectResponse response;
    ClientContext context;
    logger << "[CLIENT(TryJoinProjectClientCall)] : SENDING REQUEST\n";
    Status status = stub_->TryJoinProject(&context, request, &response);

    if (status.ok() && response.has_project()) {
        logger << "[CLIENT(TryJoinProjectClientCall)] : GOT PROJECT\n";
        project = std::move(*response.mutable_project());
        return true;
    }
    if (response.has_error_text()) {
        logger << "[CLIENT-ERROR(TryJoinProjectClientCall)] : " +
                      response.error_text() + "\n";
    } else {
        logger << "[CLIENT-WARNING(TryJoinProjectClientCall)] : STATUS IS NOT "
                  "OK\n";
    }
    return false;
}

UpdateRequests::UpdateNoteClientCall::UpdateNoteClientCall(
    const UpdateNoteRequest &request,
    CompletionQueue *cq,
    const std::unique_ptr<Update::Stub> &stub
)
    : responder_(stub->AsyncUpdateNote(&context, request, cq)) {
    context.set_deadline(
        std::chrono::system_clock::now() + std::chrono::seconds(5)
    );
    responder_->Finish(&reply_, &status, this);
    logger << "[CLIENT(UpdateNoteClientCall)] : SENDING REQUEST\n";
}

void UpdateRequests::UpdateNoteClientCall::Proceed(const bool ok) {
    if (!ok) {
        logger << "[CLIENT-WARNING(UpdateNoteClientCall)] : RPC FAILED\n";
    }
    delete this;
}

UpdateNoteResponse UpdateRequests::UpdateNoteClientCall::get_reply() {
    return reply_;
}

UpdateRequests::GetNoteClientCall::GetNoteClientCall(
    const GetNoteRequest &request,
    CompletionQueue *cq,
    const std::unique_ptr<Update::Stub> &stub
)
    : responder_(stub->AsyncGetNote(&context, request, cq)) {
    context.set_deadline(
        std::chrono::system_clock::now() + std::chrono::seconds(5)
    );
    responder_->Finish(&reply_, &status, this);
    logger << "[CLIENT(GetNoteClientCall)] : SENDING REQUEST\n";
}

void UpdateRequests::GetNoteClientCall::Proceed(const bool ok) {
    if (!ok) {
        logger << "[CLIENT-WARNING(GetNoteClientCall)] : RPC FAILED\n";
    }
    delete this;
}

GetNoteResponse UpdateRequests::GetNoteClientCall::get_reply() {
    if (!status.ok()) {
        throw std::runtime_error(status.error_message());
    }
    return reply_;
}

CreateNoteResponse UpdateRequests::CreateNoteClientCall::get_reply() {
    return reply_;
}

UpdateRequests::CreateNoteClientCall::CreateNoteClientCall(
    const CreateNoteRequest &request,
    CompletionQueue *cq,
    const std::unique_ptr<Update::Stub> &stub

)
    : responder_(stub->AsyncCreateNote(&context, request, cq)) {
    context.set_deadline(
        std::chrono::system_clock::now() + std::chrono::seconds(5)
    );
    responder_->Finish(&reply_, &status, this);
    logger << "[CLIENT(CreateNoteClientCall)] : SENDING REQUEST\n";
}

void UpdateRequests::CreateNoteClientCall::Proceed(const bool ok) {
    if (!ok) {
        logger << "[CLIENT-WARNING(CreateNoteClientCall)] : RPC FAILED\n";
    }
    delete this;
}

bool UpdateRequests::try_update_note(Note *note) const {
    UpdateNoteRequest request;
    request.mutable_note()->CopyFrom(*note);

    const auto call = new UpdateNoteClientCall(request, cq_.get(), stub_);

    void *tag;
    bool ok = false;
    if (!cq_->Next(&tag, &ok)) {
        logger << "[CLIENT-ERROR(UpdateNoteClientCall)] : CQ FAILED\n";
        return false;
    }

    if (!ok) {
        logger << "[CLIENT-WARNING(UpdateNoteClientCall)] : NO NOTE IN SERVER "
                  "REPLY\n";
        return false;
    }

    *note = call->get_reply().note();
    logger << "[CLIENT(UpdateNoteClientCall)] : UPDATE NOTE - " +
                  note->title() + "\n";
    return true;
}

bool UpdateRequests::try_fetch_note(Note *note) const {
    GetNoteRequest request;
    request.set_id(note->id());

    const auto call = new GetNoteClientCall(request, cq_.get(), stub_);

    void *tag;
    bool ok = false;
    if (!cq_->Next(&tag, &ok)) {
        logger << "[CLIENT-ERROR(GetNoteClientCall)] : CQ FAILED\n";
        return false;
    }

    if (!ok || !call->get_reply().has_note()) {
        logger << "[CLIENT-WARNING(GetNoteClientCall)] : NO NOTE IN SERVER "
                  "REPLY\n";
        return false;
    }

    *note = call->get_reply().note();
    logger << "[CLIENT-WARNING(GetNoteClientCall)] : GOT NOTE - " +
                  note->title() + "\n";
    return true;
}

bool UpdateRequests::try_create_note(
    Note *note,
    const std::string &project_code
) const {
    CreateNoteRequest request;
    request.set_project_code(project_code);
    const auto call = new CreateNoteClientCall(request, cq_.get(), stub_);

    void *tag;
    bool ok = false;
    if (!cq_->Next(&tag, &ok)) {
        logger << "[CLIENT-ERROR(CreateNoteClientCall)] : CQ FAILED\n";
        return false;
    }
    *note = call->get_reply().note();
    return true;
}

std::vector<std::string> UpdateRequests::get_project_members(
    const std::string &project_code
) const {
    GetProjectMembersRequest request;
    request.set_project_code(project_code);

    GetProjectMembersResponse response;

    ClientContext context;
    logger << "[CLIENT(GetProjectMembersClientCall)] : SENDING REQUEST\n";

    Status status = stub_->GetProjectMembers(&context, request, &response);

    if (status.ok() && response.has_members()) {
        logger << "[CLIENT(GetProjectMembersClientCall)] : GOT MEMBERS\n";

        std::vector<std::string> result;
        for (const auto &member : response.members().logins()) {
            result.push_back(member);
        }
        return result;
    }

    if (response.has_error()) {
        logger << "[CLIENT-ERROR(GetProjectMembersClientCall)] " +
                      response.error() + "\n";
    } else {
        logger << "[CLIENT-WARNING(GetProjectMembersClientCall] : STATUS IS "
                  "NOT OK\n";
    }

    return {};
}
