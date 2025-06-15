#include "server_implementation.h"

void print_logo() {
    std::cout << R"(
   / ____/ ____/ ____/  _/ ____/  _/ __ \
  / __/ / /_  / /_   / // /    / // / / /
 / /___/ __/ / __/ _/ // /____/ // /_/ /
/_____/_/   /_/   /___/\____/___/\____/
)" << std::endl;
}

int main() {
    grpc::ServerBuilder builder;
    const ServerImplementation server(50051, builder);
    print_logo();
    std::cout << "HI! WELCOME TO EFFICIO SERVER!\n"
              << "LOGS IN logs/logs.txt\n"
              << "READY. WAITING FOR REQUESTS...\n";
    server.HandleRPCs();
    return 0;
}