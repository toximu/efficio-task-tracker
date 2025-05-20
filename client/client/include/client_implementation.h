#ifndef CLIENTIMPLEMENTATION_H
#define CLIENTIMPLEMENTATION_H

#include <grpcpp/grpcpp.h>
#include "auth_requests.h"
#include "update_requests.h"

using Efficio_proto::User;
using grpc::Channel;
using grpc::CompletionQueue;

class ClientImplementation {
    CompletionQueue cq_;
    std::shared_ptr<Channel> channel_;
    UpdateRequests update_requests_;
    AuthRequests auth_requests_;

public:
    explicit ClientImplementation(const std::shared_ptr<Channel> &channel);
  
    CompletionQueue *get_cq() {
        return &cq_;
    }

    std::shared_ptr<Channel> get_channel() {
        return channel_;
    }

    void CompleteRpc();
    std::shared_ptr<Channel> get_channel();

    bool try_authenticate_user(User *user) const;
    bool try_register_user(User *user) const;

    bool try_update_note(Note *note) const;
    bool try_create_note(Note *note) const;
    bool try_fetch_note(Note *note) const;
};

#endif  // CLIENTIMPLEMENTATION_H