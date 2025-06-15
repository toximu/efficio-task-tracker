#pragma once

#include <efficio-rpc-proto/efficio.grpc.pb.h>
#include <efficio-rpc-proto/efficio.pb.h>
#include <grpc++/grpc++.h>
#include "common_server_call.h"

using grpc::ServerAsyncResponseWriter;
using grpc::ServerContext;

using Efficio_proto::Auth;

using Efficio_proto::AuthRequest;
using Efficio_proto::AuthResponse;

using Efficio_proto::DeleteUserRequest;
using Efficio_proto::DeleteUserResponse;

class AuthService final {
    Auth::AsyncService service_;
    ServerContext ctx_;
    ServerCompletionQueue *cq_;
    std::unique_ptr<grpc::Server> server_;

    class AuthServerOperation : public CommonServerCall {
    protected:
        AuthRequest request_;
        ServerAsyncResponseWriter<AuthResponse> responder_;
        Auth::AsyncService *service_;

        explicit AuthServerOperation(
            Auth::AsyncService *service,
            ServerCompletionQueue *cq
        )
            : CommonServerCall(cq), responder_(&ctx_), service_(service) {
        }

    public:
        ~AuthServerOperation() override = default;
        void Proceed(bool ok) override = 0;
    };

public:
    class TryAuthenticateUserServerCall final : public AuthServerOperation {
    public:
        explicit TryAuthenticateUserServerCall(
            Auth::AsyncService *service,
            ServerCompletionQueue *cq
        );
        void Proceed(bool) override;
    };

    class TryRegisterUserServerCall final : AuthServerOperation {
    public:
        explicit TryRegisterUserServerCall(
            Auth::AsyncService *service,
            ServerCompletionQueue *cq
        );
        void Proceed(bool) override;
    };

    class TryDeleteUserServerCall final : public CommonServerCall {
        DeleteUserRequest request_;
        ServerAsyncResponseWriter<DeleteUserResponse> responder_;
        Auth::AsyncService *service_;

    public:
        explicit TryDeleteUserServerCall(
            Auth::AsyncService *service,
            ServerCompletionQueue *cq
        );

        ~TryDeleteUserServerCall() override = default;
        void Proceed(bool) override;
    };

    Auth::AsyncService &get_service();

    explicit AuthService(ServerCompletionQueue *cq);

    void run();
};
