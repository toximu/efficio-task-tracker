#include "update_service.h"
#include "common_server_call.h"
#include "logger.hpp"
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
    logger << "[SERVER(UpdateNoteServerCall)] : START LISTENING\n";
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
            logger
                << "[SERVER(UpdateNoteServerCall)] : UPDATE NOTE REQUEST id=" +
                       std::to_string(request_.note().id()) +
                       ", title=" + response.mutable_note()->title() + "\n";
            responder_.Finish(response, grpc::Status::OK, this);
            status_ = FINISH;
            break;
        }
        case FINISH: {
            logger << "[SERVER(UpdateNoteServerCall)] : DELETING CALL\n";
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
    logger << "[SERVER(GetNoteServerCall)] : START LISTENING\n";
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

            logger << "[SERVER(GetNoteServerCall)] : FETCH NOTE REQUEST id=" +
                          std::to_string(request_.id()) +
                          ", title=" + response.note().title() + "\n";

            responder_.Finish(response, grpc::Status::OK, this);
            status_ = FINISH;
            break;
        }
        case FINISH: {
            logger << "[SERVER(GetNoteServerCal)] : DELETING CALL\n";
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
            logger << "[SERVER(GetProjectServerCall)] : START LISTENING\n";
            break;
        }
        case PROCESS: {
            new GetProjectServerCall(service_, cq_);
            status_ = FINISH;

            logger << "[SERVER(GetProjectServerCall)] : GET REQUEST, code=" +
                          request_.code() + "\n";

            UpdateHandler::get_project(request_, response_);
            responder_.Finish(response_, grpc::Status::OK, this);
            break;
        }
        case FINISH: {
            logger << "[SERVER(GetProjectServerCall)] : DELETING CALL\n";
            delete this;
        }
    }
}

UpdateService::GetProjectMembersServerCall::GetProjectMembersServerCall(
    Update::AsyncService *service,
    ServerCompletionQueue *cq
)
    : CommonServerCall(cq), responder_(&ctx_), service_(service) {
    this->Proceed(true);
}

void UpdateService::GetProjectMembersServerCall::Proceed(bool ok) {
    if (!ok) {
        delete this;
        return;
    }
    switch (status_) {
        case CREATE: {
            status_ = PROCESS;
            service_->RequestGetProjectMembers(
                &ctx_, &request_, &responder_, cq_, cq_, this
            );
            logger
                << "[SERVER(GetProjectMembersServerCall)] : START LISTENING\n";
            break;
        }
        case PROCESS: {
            status_ = FINISH;
            new CreateProjectServerCall(service_, cq_);

            logger << "[SERVER(GetProjectMembersServerCall)] : GET REQUEST, "
                      "code=" +
                          request_.project_code() + "\n";

            auto members_logins =
                ProjectDAO::get_members(request_.project_code());

            MembersList buffer;
            for (const auto &login : members_logins) {
                buffer.add_logins(login);
            }
            response_.mutable_members()->CopyFrom(buffer);

            responder_.Finish(response_, grpc::Status::OK, this);
            break;
        }
        case FINISH: {
            logger << "[SERVER(GetProjectMembersServerCall)] : DELETING CALL\n";
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
            logger << "[SERVER(CreateProjectServerCall)] : START LISTENING\n";
            break;
        }
        case PROCESS: {
            status_ = FINISH;
            new CreateProjectServerCall(service_, cq_);

            logger
                << "[SERVER(CreateProjectServerCall)] : GET REQUEST, title=" +
                       request_.project_title() + "\n";

            UpdateHandler::create_project(request_, response_);

            responder_.Finish(response_, grpc::Status::OK, this);
            break;
        }
        case FINISH: {
            logger << "[SERVER(CreateProjectServerCall)] : DELETING CALL\n";
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
            logger << "[SERVER(TryJoinProjectServerCall)] : START LISTENING\n";
            break;
        }
        case PROCESS: {
            status_ = FINISH;
            new TryJoinProjectServerCall(service_, cq_);
            logger
                << "[SERVER(TryJoinProjectServerCall)] : GET REQUEST, code=" +
                       request_.code() + "\n";

            UpdateHandler::try_join_project(request_, response_);

            responder_.Finish(response_, grpc::Status::OK, this);
            break;
        }
        case FINISH: {
            logger << "[SERVER(TryJoinProjectServerCall)] : DELETING CALL\n";
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
            logger << "[SERVER(TryLeaveProjectServerCall)] : START LISTENING\n";
            break;
        }
        case PROCESS: {
            status_ = FINISH;
            new TryLeaveProjectServerCall(service_, cq_);
            logger
                << "[SERVER(TryLeaveProjectServerCall)] : GET REQUEST, code=" +
                       request_.code() + "\n";

            UpdateHandler::try_leave_project(request_, response_);

            response_.set_ok(1);
            responder_.Finish(response_, grpc::Status::OK, this);
            break;
        }
        case FINISH: {
            logger << "[SERVER(TryLeaveProjectServerCall)] : DELETING CALL\n";
            delete this;
            break;
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
            logger << "[SERVER(CreateNoteServerCall)] : START LISTENING\n";
            break;
        }
        case PROCESS: {
            status_ = FINISH;
            new CreateNoteServerCall(service_, cq_);

            logger << "[SERVER(CreateNoteServerCall)] : GET REQUEST, title=" +
                          request_.note_title() + "\n";

            CreateNoteResponse response;
            const auto created_note =
                NoteDao::initialize_note_for_user(request_.user().login());
            ProjectDAO::add_note_to_project(
                request_.project_code(), created_note.id()
            );
            response.mutable_note()->CopyFrom(created_note);

            responder_.Finish(response, grpc::Status::OK, this);
            break;
        }
        case FINISH: {
            logger << "[SERVER(CreateNoteServerCall)] : DELETING CALL\n";
            delete this;
            break;
        }
    }
}

Update::AsyncService &UpdateService::get_service() {
    return service_;
}