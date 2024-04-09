#include "mprpcchannel.h"
#include "rpcheader.pb.h"
#include "mprpcapplication.h"
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

void mpRpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller, const google::protobuf::Message* request,
                          google::protobuf::Message* response, google::protobuf::Closure* done)
{
    const google::protobuf::ServiceDescriptor* service =  method->service();
    std::string service_name = service->name();
    std::string method_name = method->name();

    uint32_t args_size;
    std::string args_str;
    if(request->SerializeToString(&args_str)){
        // 序列化成功
        args_size = args_str.size();
    }else{
        // 序列化失败
    }
    // 定义rpc请求header
    mprpc::RpcHeader rpc_header;
    rpc_header.set_method_name(method_name);
    rpc_header.set_service_name(service_name);
    rpc_header.set_args_size(args_size);

    std::string rpc_header_str;
    // 数据头大小
    uint32_t header_size;
    if(rpc_header.SerializePartialToString(&rpc_header_str)){
        // 序列化成功
        header_size = rpc_header_str.size();
    }else{
        // 序列化失败

    }

    /*
        header_size + header_str + args_str
    */ 
    std::string send_rpc_str;
    send_rpc_str.insert(0,std::string((char*)&header_size,4));
    send_rpc_str += rpc_header_str;
    send_rpc_str += args_str;

    std::cout << "================================" << std::endl;
    std::cout << "header size :" << header_size << std::endl;
    std::cout << "header str :" << rpc_header_str << std::endl;
    std::cout << "args str :" <<args_str << std::endl;
    std::cout << "================================" << std::endl;    

    int clientfd = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == clientfd){
        std::cout << "create socket error" <<std::endl;
    }
    
    // 读取配置文件中服务端得IP地址和端口号
    std::string ip = mprpcapplication::GetInstance().GetConfig().Load("rpcservicesIP");
    uint16_t port = atoi(mprpcapplication::GetInstance().GetConfig().Load("rpcservicesPort").c_str());
    

    // 采用tcp通信，发送请求报文 
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip.c_str());

    if(-1 == connect(clientfd,(sockaddr*)&server,sizeof(server))){
        std::cout << "[connect error] errno : " << errno << std::endl;
        close(clientfd);
        exit(EXIT_FAILURE);
    }

    if(-1 == send(clientfd,send_rpc_str.c_str(),send_rpc_str.size(),0)){
        std::cout << "[send error] errno : " << errno << std::endl;
        close(clientfd);
        return;
    }

    char recv_buf[1024] = {0};
    int recv_size = 0;
    if(-1 == (recv_size = recv(clientfd,recv_buf,1024,0))){
        std::cout << "[recv error] errno : " << errno << std::endl;
        close(clientfd);
        return;
    }

    //std::string response_str(recv_buf,0,recv_size);
    //if(!response->ParseFromString(response_str)){
    if(!response->ParseFromArray(recv_buf,recv_size)){
        std::cout << "response str parse error" << std::endl;
        close(clientfd);
        return;
    }

    std::string debug;
    response->SerializeToString(&debug);
    
    
    close(clientfd);
}