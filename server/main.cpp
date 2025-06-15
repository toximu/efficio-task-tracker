#include <absl/time/time.h>
#include <grpcpp/version_info.h>
#include "server_implementation.h"

int main() {
    std::cout << "gRPC version : " << GRPC_CPP_VERSION_STRING << std::endl;

    grpc::ServerBuilder builder;
    ServerImplementation server(50051, builder);
    std::cout << "[SERVER]: WAITING FOR REQUESTS...\n";
    server.HandleRPCs();
    return 0;
}