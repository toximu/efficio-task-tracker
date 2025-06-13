#pragma once

#include <common_client_call.h>
#include <efficio-rpc-proto/efficio.grpc.pb.h>
#include <grpcpp/grpcpp.h>
#include "common_client_call.h"

using Efficio_proto::Auth;
using Efficio_proto::AuthRequest;
using Efficio_proto::AuthResponse;
using Efficio_proto::DeleteUserRequest;
using Efficio_proto::DeleteUserResponse;
using Efficio_proto::User;

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::CompletionQueue;

class AuthRequests {
public:
    explicit AuthRequests(
        const std::shared_ptr<Channel> &channel,
        const std::shared_ptr<CompletionQueue>& cq
    );

    bool try_authenticate_user(User *user) const;
    bool try_register_user(User *user) const;
    bool try_delete_user(const User *user) const;

private:
    class TryAuthenticateUserClientCall : public CommonClientCall {
    public:
        TryAuthenticateUserClientCall(
            const AuthRequest &request,
            CompletionQueue *cq,
            Auth::Stub *stub
        );
        void Proceed(bool ok) override;
        AuthResponse get_reply();

    private:
        AuthResponse reply_;
        ClientContext context;
        Status status;
        std::unique_ptr<ClientAsyncResponseReader<AuthResponse>> responder_;
    };

    class TryRegisterUserClientCall : public CommonClientCall {
    public:
        TryRegisterUserClientCall(
            const AuthRequest &request,
            CompletionQueue *cq,
            Auth::Stub *stub
        );
        void Proceed(bool ok) override;
        AuthResponse get_reply();

    private:
        AuthResponse reply_;
        ClientContext context;
        Status status;
        std::unique_ptr<ClientAsyncResponseReader<AuthResponse>> responder_;
    };

    class TryDeleteUserClientCall : public CommonClientCall {
    public:
        TryDeleteUserClientCall(
            const DeleteUserRequest &request,
            CompletionQueue *cq,
            Auth::Stub *stub
        );
        void Proceed(bool ok) override;
        DeleteUserResponse get_reply();

    private:
        DeleteUserResponse reply_;
        ClientContext context;
        Status status;
        std::unique_ptr<ClientAsyncResponseReader<DeleteUserResponse>>
            responder_;
    };

    std::unique_ptr<Auth::Stub> stub_;
    std::shared_ptr<CompletionQueue> cq_;
};