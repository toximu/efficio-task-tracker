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
using Efficio_proto::Update;

UpdateRequests::GetProjectClientCall::GetProjectClientCall(
    GetProjectRequest &request,
    CompletionQueue *cq_,
    std::unique_ptr<Update::Stub> &stub_,
    Project *save_to_
)
    : CommonClientCall(), save_to(save_to_) {
    response_reader = stub_->PrepareAsyncGetProject(&context, request, cq_);
    response_reader->StartCall();
    response_reader->Finish(&response, &status, (void *)this);
}

void UpdateRequests::GetProjectClientCall::Proceed(bool ok) {
    if (ok && status.ok()) {
        if (response.has_project()) {
            *save_to = response.project();
        } else {
            std::cout << response.error_text() << std::endl;
        }
    }
}

bool UpdateRequests::get_project(Project *project, const std::string &code) {
    auto request = new GetProjectRequest;
    request->set_code(code);
    new GetProjectClientCall(*request, cq_, stub_, project);
    return true;
}

UpdateRequests::CreateProjectClientCall::CreateProjectClientCall(
    CreateProjectRequest &request,
    CompletionQueue *cq_,
    std::unique_ptr<Update::Stub> &stub_,
    Project *save_to_) : CommonClientCall(), save_to(save_to_)
{
    response_reader = stub_->PrepareAsyncCreateProject(&context, request, cq_);
    response_reader->StartCall();
    response_reader->Finish(&response, &status, (void *)this);
}

void UpdateRequests::CreateProjectClientCall::Proceed(bool ok) {
    if (ok && status.ok()) {
        if (response.has_project()) {
            *save_to = response.project();
        } else {
            std::cout << response.error_text() << std::endl;
        }
    }
}

bool UpdateRequests::create_project(
    Project *project,
    const std::string &project_title
) {
    auto request = new CreateProjectRequest;
    request->set_project_title(project_title);
    new CreateProjectClientCall(*request, cq_, stub_, project);
    return true;
}
