#include "auth_service.h"
#include "lr_dao.hpp"

AuthService::TryAuthenticateUserCall::TryAuthenticateUserCall(
    AuthService &service,
    ServerCompletionQueue *cq
) : AuthOperation(service, cq) {
    service_.service_.RequestTryAuthenticateUser(
        &ctx_, &request_, &responder_, cq_, cq_, this
    );
    status_ = PROCESS;
}

void AuthService::TryAuthenticateUserCall::Proceed(const bool ok) {
    if (!ok) {
        delete this;
        return;
    }

    switch (status_) {
        case PROCESS: {
            new TryAuthenticateUserCall(service_, cq_);

            AuthResponse response;

            const int query_exit_code = LRDao::validate_user(
                request_.user().login(), request_.user().token()
            );

            if (query_exit_code == 1) {
                response.mutable_user()->CopyFrom(request_.user());
            } else {
                response.set_error_text(
                    "Не удалось выполнить запрос в базу данных на проверку "
                    "корректности логина и пароля"
                );
            }

            status_ = FINISH;
            break;
        }
        case FINISH: {
            delete this;
            break;
        }
    }
}

AuthService::TryRegisterUserCall::TryRegisterUserCall(
    AuthService &service,
    ServerCompletionQueue *cq
) : AuthOperation(service, cq) {
    service_.service_.RequestTryRegister1User(
        &ctx_, &request_, &responder_, cq_, cq_, this
    );
    status_ = PROCESS;
}

void AuthService::TryRegisterUserCall::Proceed(const bool ok) {
    if (!ok) {
        delete this;
        return;
    }

    switch (status_) {
        case PROCESS: {
            new TryRegisterUserCall(service_, cq_);

            AuthResponse response;

            const int query_exit_code = LRDao::try_register_user(
                request_.user().login(), request_.user().token()
            );

            if (query_exit_code < 1) {
                response.set_error_text(
                    "Не удалось выполнить запрос на запись нового пользователя "
                    "в базу данных"
                );
            } else {
                response.mutable_user()->CopyFrom(request_.user());
            }

            status_ = FINISH;
            break;
        }
        case FINISH: {
            delete this;
            break;
        }
    }
}