#include "client_implementation.h"
#include <common_client_call.h>
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <cassert>


using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

ClientImplementation::ClientImplementation(std::shared_ptr<Channel> channel) :
    channel_(channel) { };

void ClientImplementation::CompleteRpc() {

    void* got_tag;
    bool ok = false;


    while (cq_.Next(&got_tag, &ok)) {

        CommonClientCall* call = static_cast<CommonClientCall*>(got_tag);

        // Verify that the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        assert(ok);

        if (call->status.ok())
            call->Proceed();
        else
            std::cout << "RPC failed" << std::endl;

        // Once we're complete, deallocate the call object.
        delete call;
    }
}

