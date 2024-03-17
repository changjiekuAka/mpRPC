#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug;

int main()
{
    // LoginRequest req;
    // req.set_name("zhang san");
    // req.set_pwd("12345");

    // std::string str;
    // if(req.SerializeToString(&str)){
    //     std::cout << str << std::endl;
    // }

    GetFriendListsResponse rsp;
    ResultCode *rc = rsp.mutable_result();
    rc->set_errcode(1);

    user* user2 = rsp.add_friend_list();
    user2->set_age(20);
    user2->set_name("zhang san");
    user2->set_sex(user::MAN);

    std::cout << rsp.friend_list_size() << std::endl;

    return 0;
}
