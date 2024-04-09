#include "friends.pb.h"
#include "mprpcapplication.h"
#include "mprpcchannel.h"

int main(int argc,char** argv)
{
    mprpcapplication::Init(argc,argv);
    fixbug::UserServiceRpc_Stub stub(new mpRpcChannel());
    fixbug::FriendsRequest request;
    request.set_request_id(91);
    fixbug::FriendsResponse response;

    stub.GetFriendsList(nullptr,&request,&response,nullptr);

    if(0 == response.result().errcode()){
        std::cout << "rpc login response success : " << response.success() << std::endl;
        int size = response.friendlist_size();
        for(int i = 0 ; i < size; i++ )
        {
            std::cout << "friendList index [" << i <<"] name :" << response.friendlist(i) << std::endl;
        }
    }else{
        std::cout << "rpc login response error : " << response.result().errmsg() << std::endl;
    }
}