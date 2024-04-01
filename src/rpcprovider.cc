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
    if(!conn->connected())
    {
        conn->shutdown();
    }
}

void RpcProvider::OnMessage(const muduo::net::TcpConnectionPtr& conn,
                            muduo::net::Buffer* buffer,
                            muduo::Timestamp time)
{
    // 网络上接收的远程rpc调用请求的字节流数据
    std::string recv_buf = buffer->retrieveAllAsString(); 
    //获取字节流数据中header_size
    uint32_t header_size;
    recv_buf.copy((char*)&header_size,4,0);
    // 根据header_size得到header_str，并进行反序列化

    std::string rpc_header_str = recv_buf.substr(4,header_size);
    mprpc::RpcHeader rpc_header;
    
    std::string service_name;
    std::string method_name;
    uint32_t args_size;

    if(rpc_header.ParseFromString(rpc_header_str))
    {
        // 数据头反序列化成功
        service_name = rpc_header.service_name();
        method_name = rpc_header.method_name();
        args_size =  rpc_header.args_size();
    }
    else
    {
        // 数据头反序列化失败
        std::cout << "rpc_header Parse false" << std::endl;
        return; 
    }

    std::string args = rpc_header_str.substr(4 + header_size,args_size);
    
    // 打印调试信息
    std::cout << "===============================" << std::endl;
    std::cout << "rpc service name : " << service_name << std::endl;
    std::cout << "rpc method name : " << method_name << std::endl;
    std::cout << "rpc args : " << args << std::endl;
    std::cout << "===============================" << std::endl;

    auto service_it = m_serviceMap.find(service_name);
    if(service_it == m_serviceMap.end()){
        std::cout << "[error] service name no find " << std::endl;
        return;
    }

    auto method_it = service_it->second.m_methodMap.find(method_name);
    if(method_it == service_it->second.m_methodMap.end()){
        std::cout << "[error] method name no find " << std::endl;
    }

    google::protobuf::Service *service_ptr = service_it->second.m_service;
    const google::protobuf::MethodDescriptor* method_ptr = method_it->second;   
}