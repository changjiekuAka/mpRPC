#include "mprpcapplication.h"
#include "user.pb.h"
#include "mprpcchannel.h"

int main(int argc,char** argv)
{
    mprpcapplication::Init(argc,argv);

    fixbug::UserServiceRpc_Stub stub(new mpRpcChannel());
    fixbug::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("11111");

    fixbug::LoginResponse response;
    stub.Login(nullptr,&request,&response,nullptr);

    if(0 == response.result().errcode()){
        std::cout << "rpc login response success : " << response.success() << std::endl;
    }else{
        std::cout << "rpc login response error : " << response.result().errmsg() << std::endl;
    }
}