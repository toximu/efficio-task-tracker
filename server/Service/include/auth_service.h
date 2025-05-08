#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include <efficio-rpc-proto/efficio.grpc.pb.h>
#include <efficio-rpc-proto/efficio.pb.h>
#include <grpc++/grpc++.h>
#include "common_server_call.h"

using grpc::ServerAsyncResponseWriter;
using grpc::ServerContext;

using Efficio_proto::Auth;

using Efficio_proto::AuthRequest;
using Efficio_proto::AuthResponse;

class AuthService final {
    Auth::AsyncService service_;
    ServerContext ctx_;
    std::unique_ptr<ServerCompletionQueue> cq_;
    std::unique_ptr<grpc::Server> server_;

    class AuthServerOperation : public CommonServerCall {
    protected:
        AuthRequest request_;
        ServerAsyncResponseWriter<AuthResponse> responder_;
        AuthService& service_;

        explicit AuthServerOperation(
            AuthService& service,
            ServerCompletionQueue* cq
        ) : CommonServerCall(cq),
            responder_(&ctx_),
            service_(service) {}

    public:
        ~AuthServerOperation() override = default;
        void Proceed(bool ok) override = 0;
    };
public:

    class TryAuthenticateUserServerCall final : public AuthServerOperation {
    public:
        explicit TryAuthenticateUserServerCall(
            AuthService &service,
            ServerCompletionQueue *cq
        );
        void Proceed(bool) override;
    };

    class TryRegisterUserServerCall final : AuthServerOperation {
    public:
        explicit TryRegisterUserServerCall(
            AuthService &service,
            ServerCompletionQueue *cq
        );
        void Proceed(bool) override;
    };

    Auth::AsyncService &get_service();
};

#endif //AUTH_SERVICE_H
