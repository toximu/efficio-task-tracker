#include "server_implementation.h"

int main() {
    ServerImplementation server;
    std::cout << "[SERVER]: WAITING FOR REQUESTS...\n";
    server.Run(50051);
    return 0;
}