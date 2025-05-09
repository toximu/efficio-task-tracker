#ifndef AUTH_REQUESTS_H
#define AUTH_REQUESTS_H

#include <efficio-rpc-proto/efficio.grpc.pb.h>
#include <efficio-rpc-proto/efficio.pb.h>
#include <grpc++/grpc++.h>
#include "common_client_call.h"

using grpc::Channel;
using grpc::CompletionQueue;

using Efficio_proto::User;

using Efficio_proto::Auth;
using Efficio_proto::AuthRequest;
using Efficio_proto::AuthResponse;

class AuthRequests {
private:
    class AuthClientOperation : protected CommonClientCall {
    protected:
        AuthResponse reply_;
        std::unique_ptr<grpc::ClientAsyncResponseReader<AuthResponse>>
            responder_;

    public:
        AuthClientOperation(
            const AuthRequest &request,
            CompletionQueue *cq,
            const std::unique_ptr<Auth::Stub> &stub
        );
        void Proceed(bool ok) override;
        AuthResponse get_reply();
    };

    template <class Call>
    bool try_auth_operation(User *user) const {
        AuthRequest request;
        request.mutable_user()->CopyFrom(*user);

        const auto call = new Call(request, cq_, stub_);

        void *tag;
        bool ok = false;
        if (!cq_->Next(&tag, &ok)) {
            std::cout << "[CLIENT]: Completion queue failed\n";
            return false;
        }

        if (!ok) {
            std::cout << "[CLIENT WARNING]: no user in reply\n";
            return false;
        }

        *user = call->get_reply().user();
        std::cout << "[CLIENT]: USER - " << user->login() << "\n";
        return true;
    }

public:
    class TryAuthenticateUserClientCall final : public AuthClientOperation {
    public:
        TryAuthenticateUserClientCall(
            const AuthRequest &request,
            CompletionQueue *cq,
            const std::unique_ptr<Auth::Stub> &stub
        );
    };

    class TryRegisterUserClientCall final : public AuthClientOperation {
    public:
        TryRegisterUserClientCall(
            const AuthRequest &request,
            CompletionQueue *cq,
            const std::unique_ptr<Auth::Stub> &stub
        );
    };

    bool try_authenticate_user(User *user) const;
    bool try_register(User *user) const;

    explicit AuthRequests(
        const std::shared_ptr<Channel> &channel,
        CompletionQueue *cq
    )
        : cq_(cq), stub_(Auth::NewStub(channel)) {};

private:
    CompletionQueue *cq_;
    std::unique_ptr<Auth::Stub> stub_;
};

#endif  // AUTH_REQUESTS_H
