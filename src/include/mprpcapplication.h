#pragma once

class mprpcapplication
{
private:
    mprpcapplication(const mprpcapplication&) = delete;
    mprpcapplication(mprpcapplication&&) = delete;
    mprpcapplication() {}
public:
    mprpcapplication(int argc,char** argv);
    static mprpcapplication& GetInstance()
    {
        static mprpcapplication ins;
        return ins;
    }
};


