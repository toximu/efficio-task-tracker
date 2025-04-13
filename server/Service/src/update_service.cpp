#include "update_service.h"
#include "common_server_call.h"

using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;

using grpc::ServerAsyncResponseWriter;

UpdateService::GetNoteServerCall::GetNoteServerCall(UpdateService &service, ServerCompletionQueue *cq)
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
            service_.service_.RequestGetNote(
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

class UpdateService::CreateNoteServerCall final : public CommonServerCall {};

Update::AsyncService& UpdateService::get_service() {
    return service_;
}