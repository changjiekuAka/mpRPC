#include "mprpcapplication.h"

void mprpcapplication::Init(int argc,char** argv)
{

}

mprpcapplication& mprpcapplication::GetInstance()
{
    static mprpcapplication ins;
    return ins;
}
