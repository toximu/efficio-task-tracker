#include "auth_requests.h"

AuthRequests::AuthClientOperation::AuthClientOperation(
    const AuthRequest &request,
    CompletionQueue *cq,
    const std::unique_ptr<Auth::Stub> &stub
)
    : responder_(stub->AsyncTryAuthenticateUser(&context, request, cq)) {
    responder_->Finish(&reply_, &status, this);
}

void AuthRequests::AuthClientOperation::Proceed(const bool ok) {
    if (!ok) {
        std::cout << "[CLIENT WARNING]: AUTH RPC failed\n";
    }
    delete this;
}

AuthResponse AuthRequests::AuthClientOperation::get_reply() {
    return reply_;
}

AuthRequests::TryAuthenticateUserClientCall::TryAuthenticateUserClientCall(
    const AuthRequest &request,
    CompletionQueue *cq,
    const std::unique_ptr<Auth::Stub> &stub
)
    : AuthClientOperation(request, cq, stub) {
    std::cout << "[CLIENT]: AUTH USER REQUEST SENT\n";
}

AuthRequests::TryRegisterUserClientCall::TryRegisterUserClientCall(
    const AuthRequest &request,
    CompletionQueue *cq,
    const std::unique_ptr<Auth::Stub> &stub
)
    : AuthClientOperation(request, cq, stub) {
    std::cout << "[CLIENT]: REGISTER USER REQUEST SENT\n";
}

bool AuthRequests::try_authenticate_user(User *user) const {
    return try_auth_operation<TryAuthenticateUserClientCall>(user);
}

bool AuthRequests::try_register(User *user) const {
    return try_auth_operation<TryAuthenticateUserClientCall>(user);
}