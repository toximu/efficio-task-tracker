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
    new GetProjectServerCall(&service_, cq_);
    new CreateProjectServerCall(&service_, cq_);
}

UpdateService::GetNoteServerCall::GetNoteServerCall(
    Update::AsyncService *service,
    ServerCompletionQueue *cq
)
    : CommonServerCall(cq), responder_(&ctx_), service_(service) {
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

            std::cout << "[SERVER] : {get project} : get request, code="
                      << request_.code() << std::endl;
            new GetProjectServerCall(service_, cq_);
            auto *project = new Project;

            // todo: go to handler, not dao

            if (ProjectDAO::get_project(request_.code(), *project)) {
                response_.set_allocated_project(project);
            } else {
                response_.set_error_text("can't get project");
            }
            responder_.Finish(response_, grpc::Status::OK, this);
            break;
        }
        case FINISH: {
            std::cout << "[SERVER] : {get project} : deleting call" << std::endl;
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

            Project *res_project = new Project(UpdateHandler::create_project(request_.project_title()));
            response_.set_allocated_project(res_project);
            responder_.Finish(response_, grpc::Status::OK, this);
            break;
        }
        case FINISH: {
            delete this;
        }
    }
}

Update::AsyncService &UpdateService::get_service() {
    return service_;
}