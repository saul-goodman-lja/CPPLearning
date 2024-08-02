#include "../../include/online/TcpConnection.hh"
#include "../../include/online/EventLoop.hh"
#include <iostream>
#include <sstream>
TcpConnection::TcpConnection(int fd, EventLoop *loop)
: _loop(loop)
,_sockIO(fd)
, _sock(fd)
, _localAddr(getLocalAddr())
, _peerAddr(getPeerAddr()){}

TcpConnection::~TcpConnection(){}

void TcpConnection::send(const string &msg){
    _sockIO.writen(msg.c_str(), msg.size());
}

//需要做什么？
//此处的参数msg就是线程池处理好之后的可以发送出去的数据
//需要将其传递个EventLoop
//因为EventLoop本身并没有发送数据的能力，即使将线程池处理好之后的
//msg发给EventLoop，EventLoop也不能将msg发给客户端
//所有需要将发送的数据msg，以及发送数据能力的send函数，以及执行
//send函数的连接TcpConnection的对象都传递给（发送给）EventLoop，
//这样才能将数据发给客户端
void TcpConnection::sendInLoop(const string &msg){
    if(_loop){
        /* function<void()> f = bind(&TcpConnection::send, this, msg); */
        //void runInLoop(function<void()> &&)
        _loop->runInLoop(std::bind(&TcpConnection::send, this, msg));
    }
}

string TcpConnection::receive(){
    char buf[65535] = {0};
    // _sockIO.readLine(buf, sizeof(buf));
    // suggest/xxx  ||  search/xxx
    _sockIO.readTrain(buf, sizeof(buf));
    return string(buf);
}

bool TcpConnection::isClosed() const{
    char buf[10] = {0};
    int ret = ::recv(_sock.fd(), buf, sizeof(buf), MSG_PEEK);
    return (0 == ret);
}

string TcpConnection::toString(){
    std::ostringstream oss;
    oss << _localAddr.ip() << ":" << _localAddr.port() << "------>"
        << _peerAddr.ip() << ":" << _peerAddr.port();
    return oss.str();
}

//获取本端的网络地址信息
InetAddress TcpConnection::getLocalAddr(){
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    //获取本端地址的函数getsockname
    int ret = ::getsockname(_sock.fd(), (struct sockaddr*)&addr, &len);
    if(ret == -1){
        ::perror("getsockname");
    }
    return InetAddress(addr);
}

//获取对端的网络地址信息
InetAddress TcpConnection::getPeerAddr(){
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    //获取对端地址的函数getpeername
    int ret = ::getpeername(_sock.fd(), (struct sockaddr *)&addr, &len);
    if(ret == -1){
        ::perror("getpeername");
    }
    return InetAddress(addr);
}

//三个回调的注册
void TcpConnection::setNewConnectionCallback(const TcpConnectionCallback &cb){
    _onNewConnectionCb = cb;
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback &cb){
    _onMessageCb = cb;
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback &cb){
    _onCloseCb = cb;
}

//三个回调的执行
void TcpConnection::handleNewConnectionCallback(){
    if(_onNewConnectionCb){
        /* shared_ptr<TcpConnection> ttt(this); */
        /* _onNewConnectionCb(shared_ptr<TcpConnection>(this)); */
        _onNewConnectionCb(shared_from_this());
    }else{
        std::cout << "_onNewConnectionCb == nullptr" << std::endl;
    }
}

void TcpConnection::handleMessageCallback(){
    if(_onMessageCb){
        _onMessageCb(shared_from_this());
    }else{
        std::cout << "_onMessageCb == nullptr" << std::endl;
    }
}

void TcpConnection::handleCloseCallback(){
    if(_onCloseCb){
        _onCloseCb(shared_from_this());
    }else{
        std::cout << "_onClosecb == nullptr" << std::endl;
    }
}