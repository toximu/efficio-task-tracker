#include "update_service.h"
#include "common_server_call.h"
#include "note_dao.hpp"

using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;
using Efficio_proto::Note;

using grpc::ServerAsyncResponseWriter;

UpdateService::GetNoteServerCall::GetNoteServerCall(UpdateService &service, ServerCompletionQueue *cq)
    : CommonServerCall(cq),
      responder_(&ctx_),
      service_(service) {

    service_.service_.RequestGetNote(
        &ctx_,
        &request_,
        &responder_,
        cq_,
        cq_,
        this
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

            const auto note = NoteDao::get_note(request_.id(), request_.user().login());
            response.mutable_note()->CopyFrom(note);

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
        &ctx_,
        &request_,
        &responder_,
        cq_,
        cq_,
        this
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

            const auto new_note = NoteDao::initialize_note_for_user(request_.user().login());
            response.mutable_note()->CopyFrom(new_note);

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

Update::AsyncService& UpdateService::get_service() {
    return service_;
}