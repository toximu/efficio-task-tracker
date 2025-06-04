#include "server_implementation.h"
#include "common_server_call.h"

ServerImplementation::ServerImplementation(
    const uint16_t port,
    grpc::ServerBuilder &builder
)
    : cq_(builder.AddCompletionQueue()), update_service_(cq_.get()),
    auth_service_(cq_.get()) {
    builder.AddListeningPort(
        "127.0.0.1:" + std::to_string(port), grpc::InsecureServerCredentials()
    );

    builder.RegisterService(&update_service_.get_service());
    builder.RegisterService(&auth_service_.get_service());

    server_ = builder.BuildAndStart();

    update_service_.run();
    auth_service_.run();
}

void ServerImplementation::HandleRPCs() const {
    void *tag;
    bool ok;
    while (cq_->Next(&tag, &ok)) {
        static_cast<CommonServerCall *>(tag)->Proceed(ok);
    }
}
