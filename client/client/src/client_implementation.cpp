#include "client_implementation.h"
#include "update_requests.h"
#include <common_client_call.h>
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <cassert>
#include <thread>


using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

ClientImplementation::ClientImplementation(std::shared_ptr<Channel> channel) :
    channel_(channel)
     {

    // update_requests.get_project(pr);
    auto pr = new Project();
    UpdateRequests update_requests(channel_, &cq_);
    std::thread t(&ClientImplementation::CompleteRpc, this);
    std::string q;

    while (std::cin >> q) {

        update_requests.get_project(pr);

    }
    t.join();
    delete pr;

};

void ClientImplementation::CompleteRpc() {

    void* got_tag;
    bool ok = false;


    while (cq_.Next(&got_tag, &ok)) {
        std::cout << "got smth" << std::endl;
        CommonClientCall* call = static_cast<CommonClientCall*>(got_tag);

        assert(ok);

        if (call->status.ok()) {
            std::cout << "start procceed" << std::endl;
            call->Proceed();
        }
        else
            std::cout << "RPC failed" << std::endl;


        delete call;
    }
    std::cout << "complete rpc ended" << std::endl;
}

