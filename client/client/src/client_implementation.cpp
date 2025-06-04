#include "client_implementation.h"
#include <common_client_call.h>
#include <grpcpp/grpcpp.h>
#include <cassert>
#include <iostream>
#include <thread>
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
    : channel_(channel),
      update_requests_(channel, &cq_),
      auth_requests_(channel, &cq_) {
    complete_rpc_thread_ =
        std::thread(&ClientImplementation::CompleteRpc, this);

}

void ClientImplementation::CompleteRpc() {
    void *got_tag;
    bool ok = false;

    while (cq_.Next(&got_tag, &ok)) {
        std::cout << "got smth" << std::endl;
        CommonClientCall *call = static_cast<CommonClientCall *>(got_tag);

        assert(ok);

        if (call->status.ok()) {
            std::cout << "start procceed" << std::endl;
            call->Proceed();
        } else {
            std::cout << "RPC failed" << std::endl;
        }

        delete call;
    }
    std::cout << "complete rpc ended" << std::endl;
}

std::shared_ptr<Channel> ClientImplementation::get_channel() {
    return channel_;
}

CompletionQueue *ClientImplementation::get_cq() {
    return &cq_;
}

bool ClientImplementation::try_authenticate_user(User *user) {
    return auth_requests_.try_authenticate_user(user);
}

bool ClientImplementation::try_register_user(User *user) {
    return auth_requests_.try_register_user(user);
}

bool ClientImplementation::try_update_note(Note *note) {
    return update_requests_.try_update_note(note);
}

bool ClientImplementation::try_create_note(Note *note) {
    return update_requests_.try_create_note(note);
}

bool ClientImplementation::try_fetch_note(Note *note) {
    return update_requests_.try_fetch_note(note);
}

bool ClientImplementation::create_project(
    Project *project,
    const std::string &title,
    const User &user
) {
    return update_requests_.create_project(*project, title, user);
}

bool ClientImplementation::get_project(
    Project *project,
    const std::string &code
) {
    return update_requests_.get_project(*project, code);
}

bool ClientImplementation::try_join_project(Project *project, const std::string &code,const User &user) {
    return update_requests_.try_join_project(*project, code, user);
}

bool ClientImplementation::try_leave_project(
    const std::string &code,
    const User &user
) {
    return update_requests_.try_leave_project(code, user);
}


