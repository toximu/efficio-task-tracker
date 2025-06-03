#include "update_service.h"
#include "common_server_call.h"
#include "project_dao.hpp"
#include "update_handler.hpp"

using grpc::ServerAsyncResponseWriter;

using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;
using Efficio_proto::Project;

UpdateService::UpdateService(ServerCompletionQueue *cq) : cq_(cq) {
}

void UpdateService::run() {
    new GetProjectServerCall(&service_, cq_);
    new CreateProjectServerCall(&service_, cq_);
    new TryJoinProjectServerCall(&service_, cq_);
    new TryLeaveProjectServerCall(&service_, cq_);

    new GetNoteServerCall(&service_, cq_);
    new CreateNoteServerCall(&service_, cq_);
    new UpdateNoteServerCall(&service_, cq_);
}

UpdateService::UpdateNoteServerCall::UpdateNoteServerCall(
    Update::AsyncService *service,
    ServerCompletionQueue *cq
)
    : CommonServerCall(cq), responder_(&ctx_), service_(service) {
    service_->RequestUpdateNote(&ctx_, &request_, &responder_, cq_, cq_, this);
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
    Update::AsyncService *service,
    ServerCompletionQueue *cq
)
    : CommonServerCall(cq), responder_(&ctx_), service_(service) {
    service_->RequestGetNote(&ctx_, &request_, &responder_, cq_, cq_, this);
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

UpdateService::GetProjectServerCall::GetProjectServerCall(
    Update::AsyncService *service,
    ServerCompletionQueue *cq
)
    : CommonServerCall(cq), responder_(&ctx_), service_(service) {
    this->Proceed(true);
}

void UpdateService::GetProjectServerCall::Proceed(const bool ok = true) {
    switch (status_) {
        case CREATE: {
            status_ = PROCESS;
            service_->RequestGetProject(
                &ctx_, &request_, &responder_, cq_, cq_, this
            );
            std::cout << "[SERVER] : {get project} : start listening"
                      << std::endl;
            break;
        }
        case PROCESS: {
            status_ = FINISH;

            std::cout << "[SERVER] : {get project} : get request, code="
                      << request_.code() << std::endl;
            new GetProjectServerCall(service_, cq_);
            UpdateHandler::get_project(request_, response_);
            responder_.Finish(response_, grpc::Status::OK, this);
            break;
        }
        case FINISH: {
            std::cout << "[SERVER] : {get project} : deleting call"
                      << std::endl;
            delete this;
        }
    }
}

UpdateService::CreateProjectServerCall::CreateProjectServerCall(
    Update::AsyncService *service,
    ServerCompletionQueue *cq
)
    : CommonServerCall(cq), responder_(&ctx_), service_(service) {
    this->Proceed(true);
}

void UpdateService::CreateProjectServerCall::Proceed(const bool ok) {
    if (!ok) {
        delete this;
        return;
    }
    switch (status_) {
        case CREATE: {
            status_ = PROCESS;
            service_->RequestCreateProject(
                &ctx_, &request_, &responder_, cq_, cq_, this
            );
            std::cout << "[SERVER] : {create project} : start listening"
                      << std::endl;
            break;
        }
        case PROCESS: {
            status_ = FINISH;
            new GetProjectServerCall(service_, cq_);

            std::cout << "[SERVER] : {create project} : get request, title="
                      << request_.project_title() << std::endl;

            UpdateHandler::create_project(request_, response_);

            responder_.Finish(response_, grpc::Status::OK, this);
            break;
        }
        case FINISH: {
            std::cout << "[SERVER] : {create project} : deleting call"
                      << std::endl;
            delete this;
        }
    }
}

UpdateService::TryJoinProjectServerCall::TryJoinProjectServerCall(
    Update::AsyncService *service,
    ServerCompletionQueue *cq
)
    : CommonServerCall(cq), responder_(&ctx_), service_(service) {
    this->Proceed(true);
}

void UpdateService::TryJoinProjectServerCall::Proceed(const bool ok = true) {
    if (!ok) {
        delete this;
        return;
    }
    switch (status_) {
        case CREATE: {
            status_ = PROCESS;
            service_->RequestTryJoinProject(
                &ctx_, &request_, &responder_, cq_, cq_, this
            );
            std::cout << "[SERVER] : {try join project} : start listening"
                      << std::endl;
            break;
        }
        case PROCESS: {
            status_ = FINISH;
            new TryJoinProjectServerCall(service_, cq_);
            std::cout << "[SERVER] : {try join project} : get request, code="
                      << request_.code() << std::endl;

            UpdateHandler::try_join_project(request_, response_);

            responder_.Finish(response_, grpc::Status::OK, this);
            break;
        }
        case FINISH: {
            std::cout << "[SERVER] : {try join project} : deleting call"
                      << std::endl;
            delete this;
        }
    }
}

UpdateService::TryLeaveProjectServerCall::TryLeaveProjectServerCall(
    Update::AsyncService *service,
    ServerCompletionQueue *cq
)
    : CommonServerCall(cq), responder_(&ctx_), service_(service) {
    this->Proceed(true);
}

void UpdateService::TryLeaveProjectServerCall::Proceed(const bool ok) {
    if (!ok) {
        delete this;
        return;
    }
    switch (status_) {
        case CREATE: {
            status_ = PROCESS;
            service_->RequestTryLeaveProject(
                &ctx_, &request_, &responder_, cq_, cq_, this
            );
            std::cout << "[SERVER] : {try leave project} : start listening"
                      << std::endl;
            break;
        }
        case PROCESS: {
            status_ = FINISH;
            new TryLeaveProjectServerCall(service_, cq_);
            std::cout << "[SERVER] : {try leave project} : get request, code="
                      << request_.code() << std::endl;

            UpdateHandler::try_leave_project(request_, response_);

            response_.set_ok(1);
            responder_.Finish(response_, grpc::Status::OK, this);
        }
        case FINISH: {
            std::cout << "[SERVER] : {try leave project} : deleting call"
                      << std::endl;
            delete this;
        }
    }
}

UpdateService::CreateNoteServerCall::CreateNoteServerCall(
    Update::AsyncService *service,
    ServerCompletionQueue *cq
)
    : CommonServerCall(cq), responder_(&ctx_), service_(service) {
    this->Proceed(true);
}

void UpdateService::CreateNoteServerCall::Proceed(const bool ok) {
    if (!ok) {
        delete this;
        return;
    }

    switch (status_) {
        case CREATE: {
            status_ = PROCESS;
            service_->RequestCreateNote(
                &ctx_, &request_, &responder_, cq_, cq_, this
            );
            std::cout << "[SERVER] : {create note} : start listening"
                      << std::endl;
            break;
        }
        case PROCESS: {
            status_ = FINISH;
            new CreateNoteServerCall(service_, cq_);

            std::cout << "[SERVER] : {create note} : get request, title="
                      << request_.note_title() << std::endl;

            CreateNoteResponse response;
            const auto created_note =
                NoteDao::initialize_note_for_user(request_.user().login());
            response.mutable_note()->CopyFrom(created_note);

            responder_.Finish(response, grpc::Status::OK, this);
            break;
        }
        case FINISH: {
            std::cout << "[SERVER] : {create note} : deleting call"
                      << std::endl;
            delete this;
            break;
        }
    }
}

Update::AsyncService &UpdateService::get_service() {
    return service_;
}