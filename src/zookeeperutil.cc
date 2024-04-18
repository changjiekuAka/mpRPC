#include "zookeeperutil.h"
#include "mprpcapplication.h"
#include <iostream>

void global_watcher(zhandle_t *zh, int type, 
        int state, const char *path,void *watcherCtx)
{
    if(type == ZOO_SESSION_EVENT){ // 回调消息类型是和会话相关的类型，也就是连接
        if(state == ZOO_CONNECTED_STATE){ // 
            sem_t *sem = (sem_t*)zoo_get_context(zh);
            sem_post(sem);
        }
    }    
    
}


zkClient::zkClient() : m_zhandle(nullptr) {

}

zkClient::~zkClient()
{
    if(m_zhandle != nullptr){
        zookeeper_close(m_zhandle);
    }
}

void zkClient::Start()
{
    std::string zkIP = mprpcapplication::GetInstance().GetConfig().Load("ZookeeperIP");
    std::string zkPort = mprpcapplication::GetInstance().GetConfig().Load("ZookeeperPort");
    std::string conn_str = zkIP + ":" + zkPort;
    // 创建句柄连接zk服务器
    m_zhandle = zookeeper_init(conn_str.c_str(),global_watcher,30000,nullptr,nullptr,0);
    if(m_zhandle == nullptr){
        std::cout << "zookeeper_init error" << std::endl;
        exit(EXIT_FAILURE);
    }

    sem_t sem;
    sem_init(&sem,0,0);
    // 设置句柄上下文，也可以说是为句柄绑定了信号量
    zoo_set_context(m_zhandle,&sem);
    sem_wait(&sem);

    std::cout << "zookeeper init success" << std::endl;    
}

void zkClient::Create(const char *path , const char *data,int datalen,int state)
{
    char path_buffer[128];
    int bufferlen = sizeof(path_buffer);            

    int flag;
    flag = zoo_exists(m_zhandle,path,0,nullptr);
    if(flag == ZNONODE){
        flag = zoo_create(m_zhandle,path,data,datalen,
                        &ZOO_OPEN_ACL_UNSAFE,state,path_buffer,bufferlen);
        if(flag == ZOK){
            std::cout << "znode create success... path:" << path << std::endl;
        }else{
            std::cout << "flags: " << flag << std::endl;
            std::cout << "znode create err ...path:" << path << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

std::string zkClient::GetData(const char *path)
{
    char buffer[64];
    int bufferlen = sizeof(buffer);
    int flag = zoo_get(m_zhandle,path,0,buffer,&bufferlen,nullptr);
    if(flag != ZOK){
        std::cout << "get znode error... path:" << path << std::endl;
        return "";
    }else{
        return buffer;
    }

}
