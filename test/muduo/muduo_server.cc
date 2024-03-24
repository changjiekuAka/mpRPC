#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
using namespace std;
using namespace muduo;
using namespace muduo::net;

/*
    TcpServer：用于编写服务器程序
    TcpClient：用于编写客户端程序

    epoll + 线程池
    好处：能够把网络I/O的代码和业务代码区分开
*/