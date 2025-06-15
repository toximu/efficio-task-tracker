#pragma once

using grpc::ServerCompletionQueue;
using grpc::ServerContext;

class CommonServerCall {
public:
    ServerCompletionQueue *cq_;
    ServerContext ctx_;

    enum CallStatus { CREATE, PROCESS, FINISH };

    CallStatus status_;

    explicit CommonServerCall(ServerCompletionQueue *cq)
        : cq_(cq), status_(CREATE) {
    }

    virtual ~CommonServerCall() = default;

    virtual void Proceed(bool = true) = 0;
};
