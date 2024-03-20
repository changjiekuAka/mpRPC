#pragma once
#include "google/protobuf/service.h"

// 框架提供的发布Rpc服务的网络对象类
class RpcProvider
{
public:
    // 提供给外部使用的发布Rpc方法的接口
    void NotifyService(::google::protobuf::Service* service);
    // 运行Rpc服务
    void Run();
};