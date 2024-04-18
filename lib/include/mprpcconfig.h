#pragma once
#include <string>
#include <unordered_map>

class MprpcConfig
{
public:
    void LoadConfigFile(const char* filename);
    std::string Load(const std::string &key);
    void Trim(std::string &Src_buf);
private:
    std::unordered_map<std::string,std::string> m_configMap;
};