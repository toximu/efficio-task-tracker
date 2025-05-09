#include "client_implementation.h"
#include <common_client_call.h>
#include <grpcpp/grpcpp.h>
#include <cassert>
#include <iostream>
#include <thread>
#include "update_requests.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

ClientImplementation::ClientImplementation(std::shared_ptr<Channel> channel)
    : channel_(channel) {
    std::thread t(&ClientImplementation::CompleteRpc, this);
    t.detach();
};

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
