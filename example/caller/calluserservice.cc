#include "mprpcapplication.h"
#include "user.pb.h"



int main(int argc,char** argv)
{
    mprpcapplication::Init(argc,argv);

    fixbug::UserServiceRpc_Stub stub(new mpRpcChannel());
    fixbug::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("11111");

    fixbug::LoginResponse response;
    MprpcController controller;
    stub.Login(&controller,&request,&response,nullptr);

    if(controller.Failed())
    {

    }else{

        if(0 == response.result().errcode()){
            std::cout << "rpc login response success : " << response.success() << std::endl;
        }else{
            std::cout << "rpc login response error : " << response.result().errmsg() << std::endl;
        }
    }

    fixbug::RegisterRequest regis_request;
    regis_request.set_user_name("Li si");
    regis_request.set_user_msg("hello Rpc");
    regis_request.set_age(18);

    fixbug::RegisterResponse regis_response;

    stub.Register(nullptr,&regis_request,&regis_response,nullptr);

    if(0 == regis_response.result().errcode()){
        std::cout << "rpc login response success : " << regis_response.success() << std::endl;
    }else{
        std::cout << "rpc login response error : " << regis_response.result().errmsg() << std::endl;
    }
}