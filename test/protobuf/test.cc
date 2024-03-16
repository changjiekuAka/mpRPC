#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug;

int main()
{
    LoginRequest req;
    req.set_name("zhang san");
    req.set_pwd("12345");

    std::string str;
    if(req.SerializeToString(&str)){
        std::cout << str << std::endl;
    }

    return 0;
}
