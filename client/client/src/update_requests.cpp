#include <common_client_call.h>
#include <grpcpp/grpcpp.h>
#include <update_requests.h>
#include <iostream>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;
using Efficio_proto::GetProjectRequest;
using Efficio_proto::GetProjectResponse;
using Efficio_proto::TryJoinProjectRequest;
using Efficio_proto::TryJoinProjectResponse;
using Efficio_proto::TryLeaveProjectRequest;
using Efficio_proto::TryLeaveProjectResponse;
using Efficio_proto::Update;


// todo: set user everywhere

bool UpdateRequests::get_project(Project &project, const std::string &code) {
    GetProjectRequest request;

    request.set_code(code);

    GetProjectResponse response;

    ClientContext context;

    std::cout << "CLIENT : [get project] : sending request" << std::endl;

    Status status = stub_->GetProject(&context, request, &response);

    if (status.ok() && response.has_project()) {
        std::cout << "CLIENT : [get project] : got project!" << std::endl;
        project = std::move(*response.mutable_project());
        return true;
    }

    if (response.has_error_text()) {
        std::cout << "CLIENT : [create project] : error_text : "
                  << response.error_text() << std::endl;
    } else {
        std::cout << "CLIENT [create project] : status is not OK" << std::endl;
    }

    return false;
}

bool UpdateRequests::create_project(
    Project &project,
    const std::string &project_title
) {
    CreateProjectRequest request;
    request.set_project_title(project_title);

    CreateProjectResponse response;

    ClientContext context;

    std::cout << "CLIENT : [create project] : sending request" << std::endl;
    Status status = stub_->CreateProject(&context, request, &response);

    if (status.ok() && response.has_project()) {
        std::cout << "CLIENT : [create project] : got project!" << std::endl;
        project = std::move(*response.mutable_project());
        return true;
    }

    if (response.has_error_text()) {
        std::cout << "CLIENT [create project] {error text} : "
                  << response.error_text() << std::endl;
    } else {
        std::cout << "CLIENT [create project] status is not OK" << std::endl;
    }
    return false;
}

bool UpdateRequests::try_leave_project(const std::string &code) {
    TryLeaveProjectRequest request;

    request.set_code(code);
    TryLeaveProjectResponse response;
    ClientContext context;
    std::cout << "CLIENT : [try leave project] : sending request" << std::endl;
    Status status = stub_->TryLeaveProject(&context, request, &response);

    if (status.ok() && response.ok()) {
        std::cout << "CLIENT : [try leave project] : left project" << std::endl;
        return true;
    }

    std::cout << "CLIENT : [try leave project] : can't leave project"
              << std::endl;
}

bool UpdateRequests::try_join_project(
    Project &project,
    const std::string &code
) {
    TryJoinProjectRequest request;
    request.set_code(code);
    TryJoinProjectResponse response;
    ClientContext context;
    std::cout << "CLIENT : [try join project] : sending request" << std::endl;
    Status status = stub_->TryJoinProject(&context, request, &response);
    if (status.ok() && response.has_project()) {
        std::cout << "CLIENT : [try join project] : got project!" << std::endl;
        project = std::move(*response.mutable_project());
        return true;
    }
    if (response.has_error_text()) {
        std::cout << "CLIENT : [try join project] : error_text : "
                  << response.error_text() << std::endl;
    } else {
        std::cout << "CLIENT : [try join project] : status is not OK"
                  << std::endl;
    }
    return false;
}
