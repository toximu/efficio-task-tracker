#include "client_implementation.h"
#include <common_client_call.h>
#include <grpcpp/grpcpp.h>
#include <iostream>
#include "update_requests.h"
#include "update_service.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

ClientImplementation::ClientImplementation(
    const std::shared_ptr<Channel> &channel
)
    : channel_(channel), update_requests_(channel, &cq_), auth_requests_(channel, &cq_) {
}

void ClientImplementation::CompleteRpc() {
    void *tag;
    bool ok = false;

    while (cq_.Next(&tag, &ok)) {
        const auto call = static_cast<CommonClientCall *>(tag);

        if (call->status.ok()) {
            call->Proceed();
        } else {
            std::cout << "[CLIENT]: RPC failed\n";
        }

        delete call;
    }
}

std::shared_ptr<Channel> ClientImplementation::get_channel() {
    return channel_;
}

bool ClientImplementation::try_authenticate_user(User *user) const {
    return auth_requests_.try_authenticate_user(user);
}

bool ClientImplementation::try_register_user(User *user) const {
    return auth_requests_.try_register(user);
}

bool ClientImplementation::try_update_note(Note *note) const {
    return update_requests_.try_update_note(note);
}

bool ClientImplementation::try_create_note(Note *note) const {
    return update_requests_.try_create_note(note);
}

bool ClientImplementation::try_fetch_note(Note *note) const {
    return update_requests_.try_fetch_note(note);
}
