#include "TcpConnection.hh"

#include <iostream>
#include <sstream>
TcpConnection::TcpConnection(int fd)
: _sockIO(fd)
, _sock(fd)
, _localAddr(getLocalAddr())
, _peerAddr(getPeerAddr()){}

TcpConnection::~TcpConnection(){}

void TcpConnection::send(const string &msg){
    _sockIO.writen(msg.c_str(), msg.size());
}

string TcpConnection::receive(){
    char buf[65535] = {0};
    _sockIO.readLine(buf, sizeof(buf));
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