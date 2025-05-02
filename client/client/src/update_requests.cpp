#include <common_client_call.h>
#include <grpcpp/grpcpp.h>
#include <update_requests.h>
#include <iostream>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;
using Efficio_proto::GetProjectRequest;
using Efficio_proto::GetProjectResponse;
using Efficio_proto::Update;

UpdateRequests::UpdateNoteClientCall::UpdateNoteClientCall(
    const UpdateNoteRequest &request,
    grpc::CompletionQueue *cq,
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

CreateNoteResponse UpdateRequests::CreateNoteClientCall::get_reply() {
    return reply_;
}

bool UpdateRequests::update_note(Note *note) const {
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

bool UpdateRequests::fetch_note(Note *note) const {
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

bool UpdateRequests::create_note(Note *note) const {
    const CreateNoteRequest request;

    const auto call = new CreateNoteClientCall(request, cq_, stub_);

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
    std::cout << "[CLIENT]: CREATED NOTE id=" << note->id() << "\n";
    return true;
}
