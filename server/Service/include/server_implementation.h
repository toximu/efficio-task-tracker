#ifndef SERVERIMPLEMENTATION_H
#define SERVERIMPLEMENTATION_H

#include <grpc++/grpc++.h>
#include "auth_service.h"
#include "update_service.h"

using grpc::Server;
using grpc::ServerCompletionQueue;

class ServerImplementation final {
    std::unique_ptr<ServerCompletionQueue> cq_;
    std::unique_ptr<Server> server_;
    UpdateService update_service_;
    AuthService auth_service_;

public:
    explicit ServerImplementation(const uint16_t port, grpc::ServerBuilder &builder);
    void HandleRPCs();
};

#endif  // SERVERIMPLEMENTATION_H
