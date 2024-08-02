#include "../../include/online/SearchEngineServer.hh"
#include "../../include/online/TcpConnection.hh"
#include "../../include/online/MyTask.hh"
#include <iostream>
#include <string>

using std::string;

SearchEngineServer::SearchEngineServer(size_t threadNum, size_t queSize, const string &ip, unsigned short port)
: _pool(threadNum, queSize)
, _server(ip, port){}

SearchEngineServer::~SearchEngineServer(){}

// 服务器的启动与停止
void SearchEngineServer::start(){
    _pool.start();

    // 将所有的回调写到这里
    _server.setAllCallback(std::bind(&SearchEngineServer::onNewConnection, this, std::placeholders::_1)
                        , std::bind(&SearchEngineServer::onMessage, this, std::placeholders::_1)
                        , std::bind(&SearchEngineServer::onClose, this, std::placeholders::_1));
    _server.start();

}

void SearchEngineServer::stop(){
    _pool.stop();
    _server.stop();
}

// 三个回调
void SearchEngineServer::onNewConnection(const TcpConnectionPtr &con){
    std::cout << con->toString() << " has connected!!!" << std::endl;
}

void SearchEngineServer::onMessage(const TcpConnectionPtr &con){
    std::string msg = con->receive();
    std::cout << ">>>>recv from client : " << msg << std::endl;
    //接收到数据之后，可以进行业务逻辑的处理
    //处理完成之后，将其发送给客户端
    //如果在此处处理业务逻辑，并且业务逻辑的处理非常耗时，所以本
    //模型（版本）就存在缺陷，所以需要将业务逻辑的处理交给线程池
    //将接受过来的数据msg打包成任务,交给线程池
    MyTask task(msg, con);
    _pool.addTask(std::bind(&MyTask::process, task));
    // con->send(msg);
}

void SearchEngineServer::onClose(const TcpConnectionPtr &con){
    std::cout << con->toString() << " has closed!!!" << std::endl;
}