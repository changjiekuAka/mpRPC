#include <iostream>
#include <string>
#include "user.pb.h"

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
        std::string name = request->name();
        std::string pwd = request->pwd();
    }
};

int main()
{
    user tmp;
    

    return 0; 
}