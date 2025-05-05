#ifndef CLIENTIMPLEMENTATION_H
#define CLIENTIMPLEMENTATION_H

#include <grpcpp/grpcpp.h>

using grpc::CompletionQueue;
using grpc::Channel;

class ClientImplementation {
    CompletionQueue cq_;
    std::shared_ptr<Channel> channel_;
public:
    CompletionQueue *get_cq() { return &cq_; }
    std::shared_ptr<Channel> get_channel() { return channel_; }
    explicit ClientImplementation(const std::shared_ptr<Channel> &channel);
    void CompleteRpc();
};

#endif //CLIENTIMPLEMENTATION_H