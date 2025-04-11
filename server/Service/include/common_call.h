#ifndef CALL_DATA_H
#define CALL_DATA_H
#include <grpc++/grpc++.h>

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;

class CommonCall
{
public:
    ServerCompletionQueue* cq_;
    ServerContext ctx_;
    enum CallStatus { CREATE, PROCESS, FINISH };
    CallStatus status_;
public:
    explicit CommonCall(ServerCompletionQueue* cq):
          cq_(cq),
          status_(CREATE)
    {}

    virtual ~CommonCall() = default;

    virtual void Proceed(bool = true) = 0;
};


#endif