#include "auth_service.h"
#include "logger.hpp"
#include "lr_dao.hpp"
#include "project_dao.hpp"

using Efficio_proto::Storage;

AuthService::AuthService(ServerCompletionQueue *cq) : cq_(cq) {
}

AuthService::TryAuthenticateUserServerCall::TryAuthenticateUserServerCall(
    Auth::AsyncService *service,
    ServerCompletionQueue *cq
)
    : AuthServerOperation(service, cq) {
    service_->RequestTryAuthenticateUser(
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
            logger << "[SERVER(TryAuthenticateUserServerCall)] : GOT AUTH "
                      "REQUEST\n";
            new TryAuthenticateUserServerCall(service_, cq_);

            AuthResponse response;

            const int query_exit_code = LRDao::validate_user(
                request_.user().login(), request_.user().hashed_password()
            );

            if (query_exit_code == 1) {
                response.mutable_user()->CopyFrom(request_.user());
                logger
                    << "[SERVER(TryAuthenticateUserServerCall)] : WELCOME, " +
                           response.mutable_user()->login() + "\n";

                Storage user_storage;
                bool have_projects = ProjectDAO::get_all_user_projects(
                    request_.user().login(), user_storage
                );

                if (have_projects) {
                    response.mutable_user()->mutable_storage()->CopyFrom(
                        user_storage
                    );
                    logger
                        << "[SERVER(TryAuthenticateUserServerCall)] : "
                           "DOWNLOADED YOUR PROJECT " +
                               response.user().storage().projects()[0].code() +
                               " AND OTHERS\n";
                } else {
                    logger << "[SERVER(TryAuthenticateUserServerCall)] : YOU "
                              "DONT HAVE ANY PROJECTS\n";
                }

            } else {
                logger << "[SERVER-WARNING(TryAuthenticateUserServerCall)] : "
                          "SQL QUERY ERROR OR USER NOT FOUND\n";
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
    Auth::AsyncService *service,
    ServerCompletionQueue *cq
)
    : AuthServerOperation(service, cq) {
    service_->RequestTryRegisterUser(
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
            logger << "[SERVER(TryRegisterUserServerCall)] : GOT REGISTER "
                      "REQUEST\n";
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

AuthService::TryDeleteUserServerCall::TryDeleteUserServerCall(
    Auth::AsyncService *service,
    ServerCompletionQueue *cq
)
    : CommonServerCall(cq), responder_(&ctx_), service_(service) {
    service_->RequestTryDeleteUser(
        &ctx_, &request_, &responder_, cq_, cq_, this
    );
    status_ = PROCESS;
}

void AuthService::TryDeleteUserServerCall::Proceed(const bool ok) {
    if (!ok) {
        delete this;
        return;
    }

    switch (status_) {
        case PROCESS: {
            logger << "[SERVER(TryDeleteUserServerCall)] : GOT DELETE USER "
                      "REQUEST\n";
            new TryDeleteUserServerCall(service_, cq_);

            DeleteUserResponse response;

            if (LRDao::try_delete_user(request_.user().login())) {
                logger << "[SERVER(TryDeleteUserServerCall)] : DELETE USER "
                          "SUCCESSFULLY\n";
                response.set_ok(true);
            } else {
                logger << "[SERVER-WARNING(TryDeleteUserServerCall)] : DELETE "
                          "USER FAILED\n";
                response.set_ok(false);
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

void AuthService::run() {
    new TryAuthenticateUserServerCall(&service_, cq_);
    new TryRegisterUserServerCall(&service_, cq_);
}