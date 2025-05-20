#include "auth_service.h"
#include "lr_dao.hpp"

AuthService::TryAuthenticateUserServerCall::TryAuthenticateUserServerCall(
    AuthService &service,
    ServerCompletionQueue *cq
)
    : AuthServerOperation(service, cq) {
    service_.service_.RequestTryAuthenticateUser(
        &ctx_, &request_, &responder_, cq_, cq_, this
    );
    status_ = PROCESS;
}

void AuthService::TryAuthenticateUserServerCall::Proceed(const bool ok) {
    if (!ok) {
        delete this;
        return;
    }

    switch (status_) {
        case PROCESS: {
            std::cout << "[SERVER]: GOT AUTH REQUEST\n";
            new TryAuthenticateUserServerCall(service_, cq_);

            AuthResponse response;

            const int query_exit_code = LRDao::validate_user(
                request_.user().login(), request_.user().hashed_password()
            );

            if (query_exit_code == 1) {
                response.mutable_user()->CopyFrom(request_.user());
            } else {
                response.set_error_text(
                    "[SERVER ERROR]: Не удалось выполнить запрос в базу данных "
                    "на проверку "
                    "корректности логина и пароля"
                );
            }

            status_ = FINISH;
            responder_.Finish(response, grpc::Status::OK, this);
            break;
        }
        case FINISH: {
            delete this;
            break;
        }
    }
}

AuthService::TryRegisterUserServerCall::TryRegisterUserServerCall(
    AuthService &service,
    ServerCompletionQueue *cq
)
    : AuthServerOperation(service, cq) {
    service_.service_.RequestTryRegisterUser(
        &ctx_, &request_, &responder_, cq_, cq_, this
    );
    status_ = PROCESS;
}

void AuthService::TryRegisterUserServerCall::Proceed(const bool ok) {
    if (!ok) {
        delete this;
        return;
    }

    switch (status_) {
        case PROCESS: {
            std::cout << "[SERVER]: GOT REGISTER REQUEST\n";
            new TryRegisterUserServerCall(service_, cq_);

            AuthResponse response;

            const int query_exit_code = LRDao::try_register_user(
                request_.user().login(), request_.user().hashed_password()
            );

            if (query_exit_code < 1) {
                response.set_error_text(
                    "[SERVER ERROR]: Не удалось выполнить запрос на запись "
                    "нового пользователя "
                    "в базу данных"
                );
            } else {
                response.mutable_user()->CopyFrom(request_.user());
            }

            status_ = FINISH;
            responder_.Finish(response, grpc::Status::OK, this);
            break;
        }
        case FINISH: {
            delete this;
            break;
        }
    }
}

Auth::AsyncService &AuthService::get_service() {
    return service_;
}