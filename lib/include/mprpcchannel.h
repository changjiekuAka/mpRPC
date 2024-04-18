#pragma once
#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

class mpRpcChannel : public google::protobuf::RpcChannel
{
public:
    // 所有通过Stub代理对象调用得Rpc方法，都会走到这里，统一做rpc方法得数据序列化和发送
    void CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller, const google::protobuf::Message* request,
                          google::protobuf::Message* response, google::protobuf::Closure* done);
private:
};