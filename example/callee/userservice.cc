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
        return true;
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
        result->set_errmsg("888");
        response->set_success(login_result);
        
        //执行回调
        done->Run();
    }

    bool Register(std::string user,std::string msg)
    {
        std::cout << "============================" << std::endl;
        std::cout << "user :" << user <<" message : " << msg << std::endl;
        std::cout << "============================" << std::endl;
        return true;
    }


    void Register(::google::protobuf::RpcController* controller,
                       const ::fixbug::RegisterRequest* request,
                       ::fixbug::RegisterResponse* response,
                       ::google::protobuf::Closure* done)
    {
        std::string user_name = request->user_name();
        uint32_t age = request->age();
        std::string user_msg = request->user_msg();

        bool reslut_Register = Register(user_name,user_msg);

        response->set_success(reslut_Register);
        fixbug::ResultCode *reslut_code = response->mutable_result();
        reslut_code->set_errcode(0);
        reslut_code->set_errmsg("777");

        done->Run();
    }


};

int main(int argc,char** argv)
{
    //user tmp;
    mprpcapplication::Init(argc,argv);   

    RpcProvider provider;
    /* 
        provider是一个rpc网络服务类，把UserService对象发布到Rpc节点上去
        该对象需要继承于Service，才能提取服务对象描述信息和各方法描述信息，最后注册到映射表
    */
    provider.NotifyService(new user());
    // 启动一个Rpc服务站点，启动之后，进入阻塞，等待远方Rpc调用
    provider.Run();
    
    return 0; 
}