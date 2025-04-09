#include <model-proto/model.pb.h>
#include <iostream>

using namespace Efficio;
int main () {
    User user;
    user.set_user_info("dqdqd");

    Project project;
    project.add_notes(32);

    Storage storage;

    std::cout << user.user_info() << std::endl;
}