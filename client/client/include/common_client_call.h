#pragma once

#include <grpc++/grpc++.h>

using grpc::ClientContext;
using grpc::Status;

class CommonClientCall {
public:
    explicit CommonClientCall() = default;
    virtual ~CommonClientCall() = default;

    ClientContext context;
    Status status;

    virtual void Proceed(bool = true) = 0;
};
