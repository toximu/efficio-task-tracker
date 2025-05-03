#include "update_service.h"
#include "common_server_call.h"

using grpc::ServerAsyncResponseWriter;

using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;
using Efficio_proto::Project;


UpdateService::UpdateService(ServerCompletionQueue *cq) : cq_(cq), service_() {
    // new GetNoteServerCall(&service_, cq_);
}

void UpdateService::run() {
    new GetProjectServerCall(&service_, cq_);
}

UpdateService::GetNoteServerCall::GetNoteServerCall(Update::AsyncService *service, ServerCompletionQueue *cq)
    : CommonServerCall(cq),
      responder_(&ctx_),
      service_(service) {
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
) : CommonServerCall(cq), responder_(&ctx_), service_(service)
{
    this->Proceed(true);
}

void UpdateService::GetProjectServerCall::Proceed(const bool ok = true) {
    switch (status_) {
        case CREATE: {
            status_ = PROCESS;
            service_->RequestGetProject(&ctx_,&request_,&responder_, cq_, cq_, this);
            std::cout << "get project start listening" << std::endl;
            break;
        }
        case PROCESS: {
            status_ = FINISH;
            std::cout << "get project get request" << std::endl;
            new GetProjectServerCall(service_, cq_);
            auto *project = new Project;
            project->set_title("Yoo!");
            response_.set_allocated_project(project);
            responder_.Finish(response_, grpc::Status::OK, this);
            break;
        } case FINISH: {
            if (status_ == FINISH) {
                delete this;
            } else {
                std::cout << "get project why not finish" << std::endl;
            }
        }
    }
}


Update::AsyncService& UpdateService::get_service() {
    return service_;
}