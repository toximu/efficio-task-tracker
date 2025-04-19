#include "client_implementation.h"
#include "update_requests.h"
#include <common_client_call.h>
#include <grpcpp/grpcpp.h>
#include <iostream>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

ClientImplementation::ClientImplementation(
    const std::shared_ptr<Channel> &channel
)
    : channel_(channel) {
    const UpdateRequests update_requests(channel, &cq_);

    // TODO: in future we should remove id setter [NOW IT'S ONLY FOR TEST]
    const auto temp_note = new Note();
    update_requests.create_note(temp_note);
    update_requests.fetch_note(temp_note);
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
