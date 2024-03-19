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
    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {

    }
};

int main()
{
    user tmp;
    

    return 0; 
}