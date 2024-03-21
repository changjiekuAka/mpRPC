#pragma once
#include <string>
#include <unordered_map>

class MprpcConfig
{
public:
    void LoadConfigFile(const char* filename);
    std::string Load(const std::string &key);
private:
    std::unordered_map<std::string,std::string> m_configMap;
};