#include <iostream>
#include <string>
#include "user.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"

/*
UserService原来是一个本地服务，提供两个进程内的调用方法
*/

class user : public fixbug::UserServiceRpc
{
public:
    bool Login(std::string name , std::string pwd)
    {
        std::cout << "doing Local Service: Login" << std::endl;
        std::cout << name << " " << pwd << std::endl;
    }

    /*
    重写基类UserServiceRpc的虚函数，此处是在使用框架，并非编写框架
    1. caller ==》 Login(LoginRequest) ==》 muduo ==》callee
    2. caller ==》 Login(LoginRequest) ==》 交到下面重写的这个Login方法
    */
    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {
        /*
        注意这里，数据以字节流的形式传输，此时request指针已经是由Protobuf帮我们进行反序列化后的数据类型
        好处：我们无需关心数据的序列化和反序列化，Protobuf已经帮我们做好了
        */
        std::string name = request->name();
        std::string pwd = request->pwd();

        //编写本地业务
        bool login_result = Login(name,pwd);

        //编写响应 
        fixbug::ResultCode* result = response->mutable_result();
        result->set_errcode(0);
        result->set_errmsg("");
        response->set_success(login_result);
        
        //执行回调
        done->Run();
    }
};

int main(int argc,char** argv)
{
    //user tmp;
    mprpcapplication::Init(argc,argv);   

    RpcProvider provider;
    // provider是一个rpc网络服务类，把UserService对象发布到Rpc节点上去
    provider.NotifyService(new user());
    // 启动一个Rpc服务站点，启动之后，进入阻塞，等待远方Rpc调用
    provider.Run();
    
    return 0; 
}