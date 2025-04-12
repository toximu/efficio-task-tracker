#ifndef UPDATE_REQUESTS_H
#define UPDATE_REQUESTS_H

#include <grpc++/grpc++.h>
#include <efficio-rpc-proto/efficio.grpc.pb.h>
#include <efficio-rpc-proto/efficio.pb.h>

using grpc::Channel;

using Efficio_proto::Update;
using Efficio_proto::Note;
using Efficio_proto::Project;
using Efficio_proto::Storage;
class UpdateRequests {
    public:
    class GetNoteClientCall;
    class GetProjectClientCall;
    class CreateNoteClientCall;
    class CreateProjectClientCall;
    class TryJoinProjectClientCall;

    bool get_note(Note *note);
    bool get_project(Project *project);
    bool create_note(Note *note);
    bool create_project(Project *project);
    bool try_join_project(Project *project);



    explicit UpdateRequests(std::shared_ptr<Channel> channel):
        stub_(Update::NewStub(channel)) {};
    private:
    std::unique_ptr<Update::Stub> stub_;


};


#endif //UPDATE_REQUESTS_H
