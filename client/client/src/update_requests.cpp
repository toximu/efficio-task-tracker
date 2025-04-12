#include <update_requests.h>
#include <common_client_call.h>
#include <grpcpp/grpcpp.h>
#include <iostream>


using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

using Efficio_proto::GetProjectRequest;
using Efficio_proto::GetProjectResponse;
using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;
using Efficio_proto::Update;

class UpdateRequests::GetProjectClientCall : public CommonClientCall {
    GetProjectResponse response;
    std::unique_ptr<ClientAsyncResponseReader<GetProjectResponse>> response_reader;

    void Proceed(bool ok) override {

        if (ok && status.ok()) {
            if (response.has_error_string()) {
                std::cout << response.error_string() << std::endl;
            } else if (response.has_project()) {
                std::cout << response.project().title() << std::endl;
            }
        }
    }
public:
    GetProjectClientCall(const GetProjectRequest& request,
        CompletionQueue& cq_,
        std::unique_ptr<Update::Stub>& stub_) : CommonClientCall()
    {
        response_reader = stub_->AsyncGetProject(&context, request, &cq_);
        response_reader->Finish(&response, &status, (void*)this);
    }
};