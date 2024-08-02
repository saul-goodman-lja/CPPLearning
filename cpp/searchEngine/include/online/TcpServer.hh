#ifndef _TCPSERVER_HH_
#define _TCPSERVER_HH_

#include "Acceptor.hh"
#include "EventLoop.hh"

class TcpServer{
public:
    TcpServer(const string &ip, unsigned short port);
    ~TcpServer();

    //服务器启动与停止
    void start();
    void stop();

    //将三个回调一次都注册进来
    void setAllCallback(TcpConnectionCallback &&, TcpConnectionCallback &&, TcpConnectionCallback &&);
private:
    Acceptor _acceptor;
    EventLoop _loop;
};

#endif