#ifndef COMMON_CLIENT_CALL_H
#define COMMON_CLIENT_CALL_H

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

#endif  // COMMON_CLIENT_CALL_H
