#include "client_implementation.h"
#include <common_client_call.h>
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <cassert>


using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

ClientImplementation::ClientImplementation(std::shared_ptr<Channel> channel) :
    channel_(channel) { };



