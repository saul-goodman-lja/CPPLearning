#ifndef _ECHOSERVER_HH
#define _ECHOSERVER_HH

#include "ThreadPool.hh"
#include "TcpServer.hh"
#include "MyTask.hh"

class SearchEngineServer{
public:
    SearchEngineServer(size_t threadNum, size_t queSize, const string &ip, unsigned short port);
    ~SearchEngineServer();

    //服务器的启动与停止
    void start();
    void stop();

    //三个回调
    void onNewConnection(const TcpConnectionPtr &con);
    void onMessage(const TcpConnectionPtr &con);
    void onClose(const TcpConnectionPtr &con);
    void doTaskThread(const TcpConnectionPtr&, string &msg);
private:
    ThreadPool _pool;
    TcpServer _server;
};

#endif