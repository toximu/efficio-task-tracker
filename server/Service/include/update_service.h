#ifndef UPDATE_SERVICE_H
#define UPDATE_SERVICE_H

#include <grpc++/grpc++.h>
#include <model-proto/model.pb.h>
#include <efficio-rpc-proto/efficio.grpc.pb.h>
#include <efficio-rpc-proto/efficio.pb.h>

using grpc::ServerContext;

using Efficio_proto::Update;


class UpdateService final {
    Update::AsyncService service_;
    ServerContext ctx_;
public:
    class GetNoteServerCall;
    class GetProjectServerCall;
    class TryJoinProjectServerCall;
    class CreateProjectServerCall;
    class CreateNoteServerCall;
};

#endif //UPDATE_SERVICE_H
