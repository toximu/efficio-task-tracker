#include "update_requests.h"
#include <common_client_call.h>
#include <efficio-rpc-proto/efficio.grpc.pb.h>
#include <efficio-rpc-proto/efficio.pb.h>
#include <grpcpp/grpcpp.h>
#include <iostream>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

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
using Efficio_proto::User;

bool UpdateRequests::get_project(Project &project, const std::string &code) {
    GetProjectRequest request;

    request.set_code(code);

    GetProjectResponse response;

    ClientContext context;

    std::cout << "CLIENT : [get project] : sending request" << std::endl;

    Status status = stub_->GetProject(&context, request, &response);

    if (status.ok() && response.has_project()) {
        std::cout << "CLIENT : [get project] : got project!" << std::endl;
        project = std::move(*response.mutable_project());
        return true;
    }

    if (response.has_error_text()) {
        std::cout << "CLIENT : [create project] : error_text : "
                  << response.error_text() << std::endl;
    } else {
        std::cout << "CLIENT [create project] : status is not OK" << std::endl;
    }

    return false;
}

bool UpdateRequests::create_project(
    Project &project,
    const std::string &project_title,
    const User &user
) {
    CreateProjectRequest request;
    request.set_project_title(project_title);
    User *copy_user = new User(user);
    request.set_allocated_user(copy_user);

    CreateProjectResponse response;

    ClientContext context;

    std::cout << "CLIENT : [create project] : sending request" << std::endl;
    Status status = stub_->CreateProject(&context, request, &response);

    if (status.ok() && response.has_project()) {
        std::cout << "CLIENT : [create project] : got project!" << std::endl;
        project = std::move(*response.mutable_project());
        return true;
    }

    if (response.has_error_text()) {
        std::cout << "CLIENT [create project] {error text} : "
                  << response.error_text() << std::endl;
    } else {
        std::cout << "CLIENT [create project] status is not OK" << std::endl;
    }
    return false;
}

bool UpdateRequests::try_leave_project(
    const std::string &code,
    const User &user
) {
    TryLeaveProjectRequest request;

    request.set_code(code);
    User *copy_user = new User(user);
    request.set_allocated_user(copy_user);

    TryLeaveProjectResponse response;
    ClientContext context;
    std::cout << "CLIENT : [try leave project] : sending request" << std::endl;
    Status status = stub_->TryLeaveProject(&context, request, &response);

    if (status.ok() && response.ok()) {
        std::cout << "CLIENT : [try leave project] : left project" << std::endl;
        return true;
    }

    std::cout << "CLIENT : [try leave project] : can't leave project"
              << std::endl;
    return false;
}

bool UpdateRequests::try_join_project(
    Project &project,
    const std::string &code,
    const User &user
) {
    TryJoinProjectRequest request;
    request.set_code(code);
    User *copy_user = new User(user);
    request.set_allocated_user(copy_user);
    TryJoinProjectResponse response;
    ClientContext context;
    std::cout << "CLIENT : [try join project] : sending request" << std::endl;
    Status status = stub_->TryJoinProject(&context, request, &response);

    if (status.ok() && response.has_project()) {
        std::cout << "CLIENT : [try join project] : got project!" << std::endl;
        project = std::move(*response.mutable_project());
        return true;
    }
    if (response.has_error_text()) {
        std::cout << "CLIENT : [try join project] : error_text : "
                  << response.error_text() << std::endl;
    } else {
        std::cout << "CLIENT : [try join project] : status is not OK"
                  << std::endl;
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
    std::cout << "[CLIENT]: UPDATE NOTE REQUEST SENT\n";
}

void UpdateRequests::UpdateNoteClientCall::Proceed(bool ok) {
    if (!ok) {
        std::cout << "[CLIENT WARNING]: RPC failed\n";
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
    std::cout << "[CLIENT]: FETCH NOTE REQUEST SENT\n";
}

void UpdateRequests::GetNoteClientCall::Proceed(const bool ok) {
    if (!ok) {
        std::cout << "[CLIENT WARNING]: RPC failed\n";
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
    std::cout << "[CLIENT]: CREATE NOTE REQUEST SENT\n";
}

void UpdateRequests::CreateNoteClientCall::Proceed(const bool ok) {
    if (!ok) {
        std::cout << "[CLIENT WARNING]: RPC failed\n";
    }
    delete this;
}

bool UpdateRequests::try_update_note(Note *note) const {
    UpdateNoteRequest request;
    request.mutable_note()->CopyFrom(*note);

    const auto call = new UpdateNoteClientCall(request, cq_, stub_);

    void *tag;
    bool ok = false;
    if (!cq_->Next(&tag, &ok)) {
        std::cout << "[CLIENT]: Completion queue failed\n";
        return false;
    }

    if (!ok) {
        std::cout << "[CLIENT WARNING]: no note in reply\n";
        return false;
    }

    *note = call->get_reply().note();
    std::cout << "[CLIENT]: UPDATE NOTE - " << note->title() << "\n";
    return true;
}

bool UpdateRequests::try_fetch_note(Note *note) const {
    GetNoteRequest request;
    request.set_id(note->id());

    const auto call = new GetNoteClientCall(request, cq_, stub_);

    void *tag;
    bool ok = false;
    if (!cq_->Next(&tag, &ok)) {
        std::cout << "[CLIENT]: Completion queue failed\n";
        return false;
    }

    if (!ok || !call->get_reply().has_note()) {
        std::cout << "[CLIENT WARNING]: no note in reply\n";
        return false;
    }

    *note = call->get_reply().note();
    std::cout << "[CLIENT]: GOT NOTE - " << note->title() << "\n";
    return true;
}

bool UpdateRequests::try_create_note(
    Note *note,
    const std::string &project_code
) const {
    CreateNoteRequest request;
    request.set_project_code(project_code);
    const auto call = new CreateNoteClientCall(request, cq_, stub_);

    void *tag;
    bool ok = false;
    if (!cq_->Next(&tag, &ok)) {
        std::cout << "[CLIENT]: Completion queue failed\n";
        return false;
    }
    *note = call->get_reply().note();
    return true;
}
