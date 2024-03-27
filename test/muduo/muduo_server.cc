#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;
using namespace muduo;
using namespace muduo::net;

/*
    TcpServer：用于编写服务器程序
    TcpClient：用于编写客户端程序

    epoll + 线程池
    好处：能够把网络I/O的代码和业务代码区分开
*/

/*
    组合TcpServer对象
    创建EventLoop的指针
    明确TcpServer需要什么参数，输出ChatServer的构造函数
    注册用户链接处理回调，I/O事件处理回调




*/


class ChatServer
{
public:
    ChatServer(EventLoop *loop,               // 事件循环
               const InetAddress &listenAddr, // IP+PORT
               const string &nameArg)         // 服务器的名字
        : _server(loop, listenAddr, nameArg),
          _loop(loop)
    { 
        // 给服务器注册用户的连接和创建的回调
        _server.setConnectionCallback(std::bind(&ChatServer::OnConnection, this, _1));

        // 给服务器注册用户读写事件回调
        _server.setMessageCallback(std::bind(&ChatServer::OnMessage,this,_1,_2,_3));
    
        // 1个I/O线程 3个工作线程
        _server.setThreadNum(4);
    }

    void start()
    {
        _server.start();
    }
    
private:
    void OnConnection(const TcpConnectionPtr &conn)
    {
        if(conn->connected()){
            std::cout << conn->peerAddress().toIpPort() << conn->localAddress().toIpPort() << "state on" <<endl;
        }else{
            std::cout << conn->peerAddress().toIpPort() << conn->localAddress().toIpPort() << "state faile" << endl;
        }
    }

    void OnMessage(const TcpConnectionPtr &conn,
                   Buffer *buffer,
                   Timestamp time)
    {
        
    }

    TcpServer _server;
    EventLoop *_loop;
};