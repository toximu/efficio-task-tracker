#include "server_implementation.h"

int main() {
    ServerImplementation server;
    server.Run(50051);
    return 0;
}