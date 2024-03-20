#pragma once

class mprpcapplication
{
private:
    mprpcapplication(const mprpcapplication&) = delete;
    mprpcapplication(mprpcapplication&&) = delete;
    mprpcapplication() {}
public:
    static void Init(int argc,char** argv);
    static mprpcapplication& GetInstance();
   
};


