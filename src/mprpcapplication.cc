#include "mprpcapplication.h"
#include <iostream>
#include <unistd.h>

MprpcConfig mprpcapplication::m_config;

void ShowArgsHelp()
{
    std::cout << "Format: args <configfile>" << std::endl;
}
// 加载配置文件
void mprpcapplication::Init(int argc,char** argv)
{
    if(argc < 2)
    {
        ShowArgsHelp();
    }

    // 识别配置文件
    std::string config_file;
    int c = 0;
    while((c = getopt(argc,argv,"i:")) != -1)
    {
        switch (c)
        {
        case 'i':
        {
            config_file = optarg;
            break;
        }
        case '?':
        {
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        }
        case ':':
        {
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        }
        }
    }
    // 加载配置文件
    m_config.LoadConfigFile(config_file.c_str());

    // std::cout << m_config.Load("rpcservicesIP").size() << std::endl;
    // std::cout << m_config.Load("rpcservicesPort").size() << std::endl;
    // std::cout << m_config.Load("ZookeekeperIP") << std::endl;
    // std::cout << m_config.Load("ZookeekeperPort") << std::endl;

}

mprpcapplication& mprpcapplication::GetInstance()
{
    static mprpcapplication ins;
    return ins;
}

MprpcConfig& mprpcapplication::GetConfig()
{
    return m_config;
}