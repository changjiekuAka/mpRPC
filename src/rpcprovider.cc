#include "rpcprovider.h"
#include "mprpcapplication.h"
#include <functional>
#include <string>
using namespace std::placeholders;

void RpcProvider::NotifyService(::google::protobuf::Service* service)
{

}

void RpcProvider::Run()
{
    std::string ip = mprpcapplication::GetInstance().GetConfig().Load("rpcservicesIP");
    uint16_t port = std::atoi( mprpcapplication::GetInstance().GetConfig().Load("rpcservicesPort").c_str());
    muduo::net::InetAddress inetaddress(ip,port);
    
    // 组合TcpServer对象
    muduo::net::TcpServer tcpserver(&_eventloop,inetaddress,"rpcprovider");
    // 注册用户连接创捷回调
    tcpserver.setConnectionCallback(std::bind(&RpcProvider::OnConnection,this,_1));
    // 注册用户用户读写事件回调
    tcpserver.setMessageCallback(std::bind(&RpcProvider::OnMessage,this,_1,_2,_3));

    tcpserver.setThreadNum(4);

    tcpserver.start();
    _eventloop.loop();
}

void RpcProvider::OnConnection(const muduo::net::TcpConnectionPtr& conn)
{

}

void RpcProvider::OnMessage(const muduo::net::TcpConnectionPtr& conn,
                            muduo::net::Buffer* buffer,
                            muduo::Timestamp time)
                            {

                            }