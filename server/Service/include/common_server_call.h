#ifndef CALL_DATA_H
#define CALL_DATA_H
#include <grpc++/grpc++.h>


using grpc::ServerCompletionQueue;
using grpc::ServerContext;

class CommonServerCall
{
public:
    ServerCompletionQueue* cq_;
    ServerContext ctx_;
    enum CallStatus { CREATE, PROCESS, FINISH };
    CallStatus status_;
public:
    explicit CommonServerCall(ServerCompletionQueue* cq):
          cq_(cq),
          status_(CREATE)
    {}

    virtual ~CommonServerCall() = default;

    virtual void Proceed(bool = true) = 0;
};


#endif