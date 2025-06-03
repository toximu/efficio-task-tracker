#include "server_implementation.h"
#include <absl/time/time.h>

int main() {
    absl::lts_20240116::UTCTimeZone();

    grpc::ServerBuilder builder;
    ServerImplementation server(50051, builder);
    std::cout << "[SERVER]: WAITING FOR REQUESTS...\n";
    server.HandleRPCs();
    return 0;
}