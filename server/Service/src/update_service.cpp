#include "update_service.h"
#include "common_server_call.h"
#include "project_dao.hpp"
#include "update_handler.hpp"

using grpc::ServerAsyncResponseWriter;

using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;
using Efficio_proto::Project;

UpdateService::UpdateService(ServerCompletionQueue *cq) : cq_(cq), service_() {
    // new GetNoteServerCall(&service_, cq_);
}

void UpdateService::run() {
    new GetProjectServerCall(&service_, cq_.get());
    new CreateProjectServerCall(&service_, cq_.get());
}

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
        case CREATE: {
            new GetNoteServerCall(service_, cq_);
            service_->RequestGetNote(
                &ctx_, &request_, &responder_, cq_, cq_, this
            );
            status_ = PROCESS;
            break;
        }
        case PROCESS: {
            const GetNoteResponse response;
            GetNoteResponse response;

            const auto note = NoteDao::get_note(request_.id());
            response.mutable_note()->CopyFrom(note);
            std::cout << "[SERVER]: FETCH NOTE REQUEST id=" << request_.id()
                      << ", title=" << response.mutable_note()->title()
                      << ", first tag=" << response.note().tags()[0].text()
                      << ":" << response.note().tags()[0].color() << std::endl;

            // TODO: query processing logic

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

            // todo: validate user token
            // todo: check if user has this project
            std::cout << "[SERVER] : {get project} : get request, code="
                      << request_.code() << std::endl;
            new GetProjectServerCall(service_, cq_);
            auto project = UpdateHandler::get_project(request_.code());

            if (project.has_value()) {
                response_.set_allocated_project(&project.value());
            } else {
                response_.set_error_text("can't get project");
            }
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
            // todo: validate user token
            status_ = FINISH;
            new GetProjectServerCall(service_, cq_);

            std::cout << "[SERVER] : {create project} : get request, title="
                      << request_.project_title() << std::endl;

            Project *res_project = new Project(
                UpdateHandler::create_project(request_.project_title())
            );
            response_.set_allocated_project(res_project);
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
            // todo: validate user token
            // todo: check if user already has this project
            status_ = FINISH;
            new TryJoinProjectServerCall(service_, cq_);
            std::cout << "[SERVER] : {try join project} : get request, code="
                      << request_.code() << std::endl;

            if (!UpdateHandler::try_join_project(
                    request_.code(), request_.user().login()
                )) {
                response_.set_error_text("can't join project");
                responder_.Finish(response_, grpc::Status::OK, this);
                break;
            }

            auto project = UpdateHandler::get_project(request_.code());
            response_.set_allocated_project(&project.value());
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

            // todo: check if user exists, if project exists etc.
            UpdateHandler::try_leave_project(
                request_.code(), request_.user().login()
            );

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

Update::AsyncService &UpdateService::get_service() {
    return service_;
}