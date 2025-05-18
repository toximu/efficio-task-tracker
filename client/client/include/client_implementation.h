#ifndef CLIENTIMPLEMENTATION_H
#define CLIENTIMPLEMENTATION_H

#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::CompletionQueue;

class ClientImplementation {
    CompletionQueue cq_;
    std::shared_ptr<Channel> channel_;

public:
    CompletionQueue *get_cq() {
        return &cq_;
    }

    std::shared_ptr<Channel> get_channel() {
        return channel_;
    }

    explicit ClientImplementation(std::shared_ptr<Channel> channel);
    void CompleteRpc();
};

#endif  // CLIENTIMPLEMENTATION_H