#include "server_implementation.h"

int main() {
    grpc::ServerBuilder builder;
    ServerImplementation server(50051, builder);
    std::cout << "[SERVER]: WAITING FOR REQUESTS...\n";
    server.HandleRPCs();
    return 0;
}