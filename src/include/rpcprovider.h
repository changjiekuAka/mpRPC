#pragma once
#include "google/protobuf/service.h"
#include <memory>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include "google/protobuf/descriptor.h"
#include "rpcheader.pb.h"
#include <functional>
#include <string>
#include <unordered_map>


// 框架提供的发布Rpc服务的网络对象类
class RpcProvider
{
public:
    // 提供给外部使用的发布Rpc方法的接口
    void NotifyService(::google::protobuf::Service* service);
    // 运行Rpc服务
    void Run();
private:
    muduo::net::EventLoop _eventloop;

    // 组织服务对象和服务中所有的方法对象
    struct ServiceInfo
    {
        google::protobuf::Service *m_service; // 服务对象
        std::unordered_map<std::string,const google::protobuf::MethodDescriptor*> m_methodMap;
    };
    // 一个provider节点中有多个服务，组织各个服务名称和服务
    std::unordered_map<std::string,ServiceInfo> m_serviceMap;



    void OnConnection(const muduo::net::TcpConnectionPtr& conn);

    void OnMessage(const muduo::net::TcpConnectionPtr& conn,
                            muduo::net::Buffer* buffer,
                            muduo::Timestamp time);
};