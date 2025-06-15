#include <auth_requests.h>
#include <grpcpp/grpcpp.h>
#include <utility>
#include "logger.hpp"

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
    logger << "[CLIENT(TryAuthenticateUserClientCall)] : AUTHENTICATE USER "
              "REQUEST SENT\n";
}

void AuthRequests::TryAuthenticateUserClientCall::Proceed(bool ok) {
    if (!ok) {
        logger
            << "[CLIENT-WARNING(TryAuthenticateUserClientCall)] : RPC FAILED\n";
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
    logger << "[CLIENT(TryRegisterUserClientCall)] : REQUEST SENT\n";
}

void AuthRequests::TryRegisterUserClientCall::Proceed(bool ok) {
    if (!ok) {
        logger << "[CLIENT-WARNING(TryRegisterUserClientCall)] : RPC FAILED\n";
    }
    delete this;
}

AuthResponse AuthRequests::TryRegisterUserClientCall::get_reply() {
    return reply_;
}

AuthRequests::TryDeleteUserClientCall::TryDeleteUserClientCall(
    const DeleteUserRequest &request,
    CompletionQueue *cq,
    Auth::Stub *stub
)
    : responder_(stub->AsyncTryDeleteUser(&context, request, cq)) {
    responder_->Finish(&reply_, &status, this);
    logger << "[CLIENT(TryDeleteUserClientCall)] : REQUEST SENT\n";
}

void AuthRequests::TryDeleteUserClientCall::Proceed(bool ok) {
    if (!ok) {
        logger << "[CLIENT-WARNING(TryDeleteUserClientCall)] : RPC FAILED\n";
    }
    delete this;
}

DeleteUserResponse AuthRequests::TryDeleteUserClientCall::get_reply() {
    return reply_;
}

AuthRequests::AuthRequests(
    const std::shared_ptr<Channel> &channel,
    std::shared_ptr<CompletionQueue> cq
)
    : stub_(Auth::NewStub(channel)), cq_(std::move(cq)) {
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
        logger << "[CLIENT(TryAuthenticateUserClientCall)] : CQ FAILED\n";
        return false;
    }

    if (!ok || call->get_reply().has_error_text()) {
        logger << "[CLIENT-WARNING(TryAuthenticateUserClientCall)] : "
                  "AUTHENTICATION FAILED\n";
        return false;
    }

    user->CopyFrom(call->get_reply().user());
    logger << "[CLIENT(TryAuthenticateUserClientCal)] : AUTHENTICATED USER - " +
                  user->login() + "\n";
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
        logger << "[CLIENT(TryRegisterUserClientCall)] : CQ FAILED\n";
        return false;
    }

    if (!ok || call->get_reply().has_error_text()) {
        logger << "[CLIENT-WARNING(TryRegisterUserClientCall)] : REGISTRATION "
                  "FAILED\n";
        return false;
    }

    user->CopyFrom(call->get_reply().user());
    logger
        << "[CLIENT-WARNING(TryRegisterUserClientCall)] : REGISTERED USER - " +
               user->login() + "\n";
    return true;
}

bool AuthRequests::try_delete_user(const User *user) const {
    DeleteUserRequest request;
    request.mutable_user()->set_login(user->login());

    const auto call =
        new TryDeleteUserClientCall(request, cq_.get(), stub_.get());

    void *tag;
    bool ok = false;
    if (!cq_->Next(&tag, &ok)) {
        logger << "[CLIENT(TryDeleteUserClientCall)] : CQ FAILED\n";
        return false;
    }

    if (!ok || !call->get_reply().ok()) {
        logger
            << "[CLIENT-WARNING(TryDeleteUserClientCall)] : DELETING FAILED\n";
        return false;
    }

    logger << "[CLIENT(TryDeleteUserClientCall)] : USER DELETED\n";
    return true;
}