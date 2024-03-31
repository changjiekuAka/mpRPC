#include "rpcprovider.h"
#include "mprpcapplication.h"

using namespace std::placeholders;

// 这里是框架提供给外部使用的，可以发布rpc方法
void RpcProvider::NotifyService(::google::protobuf::Service* service)
{
    ServiceInfo service_info;

    // 获取服务对象的描述信息
    const google::protobuf::ServiceDescriptor *pserviceDesc =  service->GetDescriptor();
    // 从描述信息中拿到服务对象名字
    std::string service_name = pserviceDesc->name();
    // 从描述信息中拿到服务对象中方法的数量
    int method_count = pserviceDesc->method_count();

    std::cout << service_name << std::endl;

    for(int i = 0;i < method_count;++i)
    {
        const google::protobuf::MethodDescriptor *pmethodDesc = pserviceDesc->method(i);
        std::string method_name = pmethodDesc->name();
        
        std::cout << method_name << std::endl;
        
        service_info.m_methodMap.insert({ service_name , pmethodDesc});
    }
    m_serviceMap.insert({service_name , service_info});
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