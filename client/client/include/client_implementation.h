#ifndef CLIENTIMPLEMENTATION_H
#define CLIENTIMPLEMENTATION_H

#include <grpcpp/grpcpp.h>
#include "auth_requests.h"
#include "update_requests.h"

using Efficio_proto::User;
using grpc::Channel;
using grpc::CompletionQueue;

class ClientImplementation {
    static CompletionQueue cq_;
    static std::shared_ptr<Channel> channel_;
    static UpdateRequests update_requests_;
    static AuthRequests auth_requests_;

    static void init();

    ClientImplementation() = default;

public:
    static ClientImplementation &get_instance();

    void CompleteRpc();
    std::shared_ptr<Channel> get_channel();
    CompletionQueue *get_cq();

    bool try_authenticate_user(User *user);
    bool try_register_user(User *user);

    bool try_update_note(Note *note);
    bool try_create_note(Note *note);
    bool try_fetch_note(Note *note);
};

#endif  // CLIENTIMPLEMENTATION_H