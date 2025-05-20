#include "server_implementation.h"
#include "common_server_call.h"

using Efficio_proto::GetNoteRequest;

void ServerImplementation::Run(const uint16_t port) {
    grpc::ServerBuilder builder;
    cq_ = builder.AddCompletionQueue();
    builder.AddListeningPort(
        "localhost:" + std::to_string(port), grpc::InsecureServerCredentials()
    );
    builder.RegisterService(&update_service_.get_service());
    builder.RegisterService(&auth_service_.get_service());

    cq_ = builder.AddCompletionQueue();
    server_ = builder.BuildAndStart();
    UpdateService update_service(cq_.get());
    update_service.run();
    HandleRPCs();
}

void ServerImplementation::HandleRPCs() {
    new UpdateService::GetNoteServerCall(update_service_, cq_.get());
    new UpdateService::CreateNoteServerCall(update_service_, cq_.get());
    new UpdateService::UpdateNoteServerCall(update_service_, cq_.get());

    new AuthService::TryAuthenticateUserServerCall(auth_service_, cq_.get());
    new AuthService::TryRegisterUserServerCall(auth_service_, cq_.get());
  
    void *tag;
    bool ok;
    while (cq_->Next(&tag, &ok)) {
        static_cast<CommonServerCall *>(tag)->Proceed(ok);
    }
}
