#include <model-proto/model.pb.h>
#include "client_implementation.h"
#include "update_requests.h"

using Efficio_proto::Project;
using grpc::Channel;

int main() {
    ClientImplementation client(
        grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()
        )
    );

    User user;
    user.set_login("toximu");
    user.set_hashed_password("12345678");

    // client.try_register_user(&user); ok

    Project *project = new Project;

    // client.create_project(project, "ttt", user); ok

    // std::cout << project->DebugString() << std::endl;

    // client.get_project(project, "JUSIBT");

    // std::cout << project->DebugString() << std::endl;

    Note *note = new Note;

    // client.try_create_note(note); ok, but note should be added to project
    // aswell

    note->set_id(1);
    note->set_title("neww");
    note->set_text("some texttt");
    // client.try_fetch_note(note); // not ok, oshibka
    // std::cout << "Note id : " << note->id() << ", title : " << note->title()
    // << std::endl;

    // client.try_update_note(note); // ok

    std::cout << note->DebugString() << std::endl;

    User user2;
    user2.set_login("usr");
    user2.set_hashed_password("12345678");

    Project *project_to_join = new Project;

    // client.try_join_project(project_to_join, "ML05B3", user2); // ok

    // std::cout << project_to_join->DebugString() << std::endl;

    // client.try_leave_project("ML05B3", user2); // ok

    client.complete_rpc_thread_.join();
}
