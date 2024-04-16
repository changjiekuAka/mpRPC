#pragma once

#include <semaphore.h>
#include <zookeeper/zookeeper.h>
#include <string>

class zkClient
{
public:
    zkClient();
    ~zkClient();
    // zkClient启动自动连接zkServer
    void Start();
    // 在zkServer中根据指定的path创建一个znode
    void Create(const char *path , const char *data,int datalen,int state = 0);
    // 获取指定path的data数据
    std::string GetData(const char *path);
private:
    zhandle_t *m_zhandle;
};
