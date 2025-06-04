#include <auth_requests.h>
#include <grpcpp/grpcpp.h>
#include <iostream>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

using Efficio_proto::Auth;
using Efficio_proto::AuthRequest;
using Efficio_proto::AuthResponse;
using Efficio_proto::User;

AuthRequests::TryAuthenticateUserClientCall::TryAuthenticateUserClientCall(
    const AuthRequest &request,
    CompletionQueue *cq,
    Auth::Stub *stub
)
    : responder_(stub->AsyncTryAuthenticateUser(&context, request, cq)) {
    context.set_deadline(
        std::chrono::system_clock::now() + std::chrono::seconds(5)
    );
    responder_->Finish(&reply_, &status, this);
    std::cout << "[CLIENT]: AUTHENTICATE USER REQUEST SENT\n";
}

void AuthRequests::TryAuthenticateUserClientCall::Proceed(bool ok) {
    if (!ok) {
        std::cout << "[CLIENT WARNING]: Authentication RPC failed\n";
    }
    delete this;
}

AuthResponse AuthRequests::TryAuthenticateUserClientCall::get_reply() {
    return reply_;
}

AuthRequests::TryRegisterUserClientCall::TryRegisterUserClientCall(
    const AuthRequest &request,
    CompletionQueue *cq,
    Auth::Stub *stub
)
    : responder_(stub->AsyncTryRegisterUser(&context, request, cq)) {
    context.set_deadline(
        std::chrono::system_clock::now() + std::chrono::seconds(5)
    );
    responder_->Finish(&reply_, &status, this);
    std::cout << "[CLIENT]: REGISTER USER REQUEST SENT\n";
}

void AuthRequests::TryRegisterUserClientCall::Proceed(bool ok) {
    if (!ok) {
        std::cout << "[CLIENT WARNING]: Registration RPC failed\n";
    }
    delete this;
}

AuthResponse AuthRequests::TryRegisterUserClientCall::get_reply() {
    return reply_;
}

AuthRequests::AuthRequests(
    const std::shared_ptr<Channel> &channel,
    CompletionQueue *cq
)
    : stub_(Auth::NewStub(channel)), cq_(cq) {
}

bool AuthRequests::try_authenticate_user(User *user) const {
    AuthRequest request;
    request.mutable_user()->set_login(user->login());
    request.mutable_user()->set_hashed_password(user->hashed_password());

    const auto call =
        new TryAuthenticateUserClientCall(request, cq_.get(), stub_.get());

    void *tag;
    bool ok = false;
    if (!cq_->Next(&tag, &ok)) {
        std::cout << "[CLIENT]: Completion queue failed\n";
        return false;
    }

    if (!ok) {
        std::cout << "[CLIENT WARNING]: Authentication failed\n";
        return false;
    }

    user->CopyFrom(call->get_reply().user());
    std::cout << "[CLIENT]: AUTHENTICATED USER - " << user->login() << "\n";
    return true;
}

bool AuthRequests::try_register_user(User *user) const {
    AuthRequest request;
    request.mutable_user()->set_login(user->login());
    request.mutable_user()->set_hashed_password(user->hashed_password());

    const auto call =
        new TryRegisterUserClientCall(request, cq_.get(), stub_.get());

    void *tag;
    bool ok = false;
    if (!cq_->Next(&tag, &ok)) {
        std::cout << "[CLIENT]: Completion queue failed\n";
        return false;
    }

    if (!ok) {
        std::cout << "[CLIENT WARNING]: Registration failed\n";
        return false;
    }

    user->CopyFrom(call->get_reply().user());
    std::cout << "[CLIENT]: REGISTERED USER - " << user->login() << "\n";
    return true;
}