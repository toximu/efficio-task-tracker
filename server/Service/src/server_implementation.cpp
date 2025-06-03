#include "server_implementation.h"
#include "common_server_call.h"

ServerImplementation::ServerImplementation(
    const uint16_t port,
    grpc::ServerBuilder &builder
)
    : cq_(builder.AddCompletionQueue()), update_service_(cq_.get()) {
    cq_ = builder.AddCompletionQueue();
    builder.AddListeningPort(
        "localhost:" + std::to_string(port), grpc::InsecureServerCredentials()
    );

    builder.RegisterService(&update_service_.get_service());
    builder.RegisterService(&auth_service_.get_service());

    update_service_.run();
    auth_service_.run();

    server_ = builder.BuildAndStart();
}

void ServerImplementation::HandleRPCs() const {
    void *tag;
    bool ok;
    while (cq_->Next(&tag, &ok)) {
        static_cast<CommonServerCall *>(tag)->Proceed(ok);
    }
}
