#include "update_service.h"
#include "common_server_call.h"
#include "note_dao.hpp"

using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;
using Efficio_proto::Note;

using grpc::ServerAsyncResponseWriter;

UpdateService::UpdateNoteServerCall::UpdateNoteServerCall(
    UpdateService &service,
    ServerCompletionQueue *cq
)
    : CommonServerCall(cq), responder_(&ctx_), service_(service) {
    service_.service_.RequestUpdateNote(
        &ctx_, &request_, &responder_, cq_, cq_, this
    );
    status_ = PROCESS;
}

void UpdateService::UpdateNoteServerCall::Proceed(const bool ok) {
    if (!ok) {
        delete this;
        return;
    }

    switch (status_) {
        case PROCESS: {
            new UpdateNoteServerCall(service_, cq_);

            UpdateNoteResponse response;

            NoteDao::update_note(request_.note());
            response.mutable_note()->CopyFrom(request_.note());
            std::cout << "[SERVER]: UPDATE NOTE REQUEST id="
                      << request_.note().id()
                      << ", title=" << response.mutable_note()->title()
                      << std::endl;
            responder_.Finish(response, grpc::Status::OK, this);
            status_ = FINISH;
            break;
        }
        case FINISH: {
            delete this;
            break;
        }
    }
}

UpdateService::GetNoteServerCall::GetNoteServerCall(
    UpdateService &service,
    ServerCompletionQueue *cq
)
    : CommonServerCall(cq), responder_(&ctx_), service_(service) {
    service_.service_.RequestGetNote(
        &ctx_, &request_, &responder_, cq_, cq_, this
    );
    status_ = PROCESS;
}

void UpdateService::GetNoteServerCall::Proceed(const bool ok) {
    if (!ok) {
        delete this;
        return;
    }

    switch (status_) {
        case PROCESS: {
            new GetNoteServerCall(service_, cq_);

            GetNoteResponse response;

            const auto note = NoteDao::get_note(request_.id());
            response.mutable_note()->CopyFrom(note);
            std::cout << "[SERVER]: FETCH NOTE REQUEST id=" << request_.id()
                      << ", title=" << response.mutable_note()->title()
                      << ", first tag=" << response.note().tags()[0].text()
                      << ":" << response.note().tags()[0].color() << std::endl;

            responder_.Finish(response, grpc::Status::OK, this);
            status_ = FINISH;
            break;
        }
        case FINISH: {
            delete this;
            break;
        }
    }
}

UpdateService::CreateNoteServerCall::CreateNoteServerCall(
    UpdateService &service,
    ServerCompletionQueue *cq
)
    : CommonServerCall(cq), responder_(&ctx_), service_(service) {
    service_.service_.RequestCreateNote(
        &ctx_, &request_, &responder_, cq_, cq_, this
    );
    status_ = PROCESS;
}

void UpdateService::CreateNoteServerCall::Proceed(const bool ok) {
    if (!ok) {
        delete this;
        return;
    }

    switch (status_) {
        case PROCESS: {
            new CreateNoteServerCall(service_, cq_);
            CreateNoteResponse response;

            const auto new_note =
                NoteDao::initialize_note_for_user(request_.user().login());
            response.mutable_note()->CopyFrom(new_note);

            std::cout << "[SERVER]: CREATE NOTE REQUEST id=" << new_note.id()
                      << std::endl;

            responder_.Finish(response, grpc::Status::OK, this);
            status_ = FINISH;
            break;
        }
        case FINISH: {
            delete this;
            break;
        }
    }
}

Update::AsyncService &UpdateService::get_service() {
    return service_;
}