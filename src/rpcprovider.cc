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
    std::string ip = mprpcapplication::GetInstance().GetConfig().Load("rpcserverip");
    uint16_t port = std::stoi( mprpcapplication::GetInstance().GetConfig().Load("rpcserverport").c_str());
    muduo::net::InetAddress inetaddress(ip,port);

    muduo::net::TcpServer m_tcpserver(&_eventloop,inetaddress,"rpcprovider");

    m_tcpserver.setConnectionCallback(std::bind(&RpcProvider::OnConnection,this,_1));

    m_tcpserver.setMessageCallback(std::bind(&RpcProvider::OnMessage,this,_1,_2,_3));

}

void RpcProvider::OnConnection(const muduo::net::TcpConnectionPtr& conn)
{

}

void RpcProvider::OnMessage(const muduo::net::TcpConnectionPtr& conn,
                            muduo::net::Buffer* buffer,
                            muduo::Timestamp time)
                            {

                            }