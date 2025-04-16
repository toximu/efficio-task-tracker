#include "server_implementation.h"

int main() {
    ServerImplementation server;
    std::cout << "Preparing...\n";
    server.Run(50051);
    std::cout << "Server started!\n";
    return 0;
}