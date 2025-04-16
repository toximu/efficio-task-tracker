#include "server_implementation.h"
#include "common_server_call.h"

using Efficio_proto::GetNoteRequest;

void ServerImplementation::Run(const uint16_t port) {
    grpc::ServerBuilder builder;
    UpdateService update_service;

    builder.AddListeningPort(
        "127.0.0.1:" + std::to_string(port), grpc::InsecureServerCredentials()
    );
    builder.RegisterService(&update_service.get_service());
    cq_ = builder.AddCompletionQueue();
    server_ = builder.BuildAndStart();
    HandleRPCs(update_service);
}

void ServerImplementation::HandleRPCs(UpdateService& update_service) const {
    new UpdateService::GetNoteServerCall(update_service, cq_.get());
    new UpdateService::CreateNoteServerCall(update_service, cq_.get());

    void* tag;
    bool ok;
    while (cq_->Next(&tag, &ok)) {
        static_cast<CommonServerCall*>(tag)->Proceed(ok);
    }
}
