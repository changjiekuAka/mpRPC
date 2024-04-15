#include "friends.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
#include "logger.h"
#include <iostream>
#include <vector>
#include <string>

class friends : public fixbug::UserServiceRpc
{
    bool GetFriendsList(uint32_t request_id , std::vector<std::string> &friendlist)
    {
        std::cout << " request_id : " << request_id << "request friendList" << std::endl;
        friendlist.push_back("Zhang san");
        friendlist.push_back("wang seng meng");
        friendlist.push_back("Yu hong gang");
        return true;
    }


    void GetFriendsList(::google::protobuf::RpcController* controller,
                       const ::fixbug::FriendsRequest* request,
                       ::fixbug::FriendsResponse* response,
                       ::google::protobuf::Closure* done)
    {
        uint32_t id = request->request_id();
        std::vector<std::string> friendList;
        bool Get_reslut = GetFriendsList(id,friendList);

        response->set_success(Get_reslut);
        fixbug::ResultCode *reslut = response->mutable_result();
        reslut->set_errcode(0);
        reslut->set_errmsg("999");

        for(std::string& name : friendList){
            std::string *p = response->add_friendlist();
            *p = name; 
        }
        done->Run();
    }
};

int main(int argc,char** argv)
{
    LOG_INFO("first log msg");
    LOG_INFO("%s-%s-%d",__FILE__,__FUNCTION__,__LINE__);

    //user tmp;
    mprpcapplication::Init(argc,argv);   

    RpcProvider provider;
    /* 
        provider是一个rpc网络服务类，把UserService对象发布到Rpc节点上去
        该对象需要继承于Service，才能提取服务对象描述信息和各方法描述信息，最后注册到映射表
    */
    provider.NotifyService(new friends());
    // 启动一个Rpc服务站点，启动之后，进入阻塞，等待远方Rpc调用
    provider.Run();
    
    return 0; 
}