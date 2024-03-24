#include "mprpcconfig.h"

void MprpcConfig::LoadConfigFile(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == nullptr)
    {
        // 文件不存在
    }
    while (!feof(fp))
    {
        char buffer[512];
        fgets(buffer, 512, fp);

        // 去前后空格字符
        std::string src_buf(buffer);

        Trim(src_buf);

        // 注释跳过、去完空格为空跳过
        if (src_buf[0] == '#' || src_buf.empty())
        {
            continue;
        }

        int idx = src_buf.find('=');
        if (idx == -1)
        {
            // 配置不合法
            break;
        }
        std::string key = src_buf.substr(0, idx);
        Trim(key);

        std::string value;
        int idx_end = src_buf.find('\n');
        if(idx_end != -1)
        {
            value = src_buf.substr(idx + 1, src_buf.size() - idx - 2);
        }else{
            value = src_buf.substr(idx + 1, src_buf.size() - idx - 1);
        }
        Trim(value);

        m_configMap.insert({key, value});
    }
}

std::string MprpcConfig::Load(const std::string &key)
{
    // 这里不能使用[]，使用后会往map里面插入不必要的数据
    auto it = m_configMap.find(key);
    if (it == m_configMap.end())
    {
        return "";
    }
    return it->second;
}

void MprpcConfig::Trim(std::string &src_buf)
{
    // 去前空格字符
    int idx = src_buf.find_first_not_of(' ');
    if (idx != -1)
    {
        src_buf = src_buf.substr(idx, src_buf.size() - idx);
    }
    // 去后空格字符
    idx = src_buf.find_last_not_of(' ');
    if (idx != -1)
    {
        src_buf = src_buf.substr(0, idx + 1);
    }
}