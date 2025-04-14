#include "server_implementation.h"
#include "common_server_call.h"

using Efficio_proto::GetNoteRequest;

void ServerImplementation::Run(const uint16_t port) {
    grpc::ServerBuilder builder;
    cq_ = builder.AddCompletionQueue();
    builder.AddListeningPort(
        "localhost:" + std::to_string(port), grpc::InsecureServerCredentials()
    );


    UpdateService update_service(cq_.get());
    builder.RegisterService(&update_service.get_service());
    server_ = builder.BuildAndStart();
    update_service.run();
    HandleRPCs();
}

void ServerImplementation::HandleRPCs() const {
    void *tag;
    bool ok;
    while (cq_->Next(&tag, &ok)) {
        static_cast<CommonServerCall*>(tag)->Proceed(ok);
    }
}
