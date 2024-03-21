#pragma once
#include "mprpcconfig.h"

class mprpcapplication
{
private:
    mprpcapplication(const mprpcapplication&) = delete;
    mprpcapplication(mprpcapplication&&) = delete;
    mprpcapplication() {}
    static MprpcConfig m_config;
public:
    static void Init(int argc,char** argv);
    static mprpcapplication& GetInstance();
   
};


