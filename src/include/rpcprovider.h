#pragma once
#include "google/protobuf/service.h"
#include <memory>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>

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

    void OnConnection(const muduo::net::TcpConnectionPtr& conn);

    void OnMessage(const muduo::net::TcpConnectionPtr& conn,
                            muduo::net::Buffer* buffer,
                            muduo::Timestamp time);
};