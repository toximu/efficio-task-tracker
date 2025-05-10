#ifndef CLIENTIMPLEMENTATION_H
#define CLIENTIMPLEMENTATION_H

#include <grpcpp/grpcpp.h>
#include "update_requests.h"

using grpc::Channel;

class ClientImplementation {
    grpc::CompletionQueue cq_;
    std::shared_ptr<Channel> channel_;
    UpdateRequests update_requests_;

public:
    std::shared_ptr<Channel> get_channel() {
        return channel_;
    }

    explicit ClientImplementation(const std::shared_ptr<Channel> &channel);
    void CompleteRpc();

    bool try_update_note(Note *note) const;
    bool try_create_note(Note *note) const;
    bool try_fetch_note(Note *note) const;
};

#endif  // CLIENTIMPLEMENTATION_H