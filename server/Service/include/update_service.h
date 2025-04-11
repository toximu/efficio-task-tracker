#ifndef UPDATE_SERVICE_H
#define UPDATE_SERVICE_H

#include <grpc++/grpc++.h>
#include <model-proto/model.pb.h>
#include <efficio-rpc-proto/efficio.grpc.pb.h>
#include <efficio-rpc-proto/efficio.pb.h>


using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;


using Efficio_proto::Update;


class UpdateService final {
    Update::AsyncService service_;

public:
    class GetNoteCall;
    // ...
    void Run(uint16_t port);
};

#endif //UPDATE_SERVICE_H
