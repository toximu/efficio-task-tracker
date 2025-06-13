#ifndef CLIENTIMPLEMENTATION_H
#define CLIENTIMPLEMENTATION_H

#include <grpcpp/grpcpp.h>
#include <thread>
#include "auth_requests.h"
#include "update_requests.h"

using Efficio_proto::User;
using grpc::Channel;
using grpc::CompletionQueue;

class ClientImplementation {
    std::shared_ptr<CompletionQueue> cq_;
    std::shared_ptr<Channel> channel_;
    UpdateRequests update_requests_;
    AuthRequests auth_requests_;
    std::thread complete_rpc_thread_;

public:
    explicit ClientImplementation(const std::shared_ptr<Channel> &channel);
    ~ClientImplementation();

    void CompleteRpc();
    std::shared_ptr<Channel> get_channel();
    CompletionQueue *get_cq();

    bool try_authenticate_user(User *user);
    bool try_register_user(User *user);
    bool try_delete_user(const User *user) const;

    bool try_update_note(Note *note) const;
    bool try_create_note(Note *note, const std::string &project_code) const;
    bool try_fetch_note(Note *note) const;

    bool create_project(
        Project *project,
        const std::string &title,
        const User &user
    );
    bool get_project(Project *project, const std::string &code);
    bool try_join_project(
        Project *project,
        const std::string &code,
        const User &user
    );
    bool try_leave_project(const std::string &code, const User &user);

};

#endif  // CLIENTIMPLEMENTATION_H