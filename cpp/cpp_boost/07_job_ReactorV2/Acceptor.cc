#include "Acceptor.hh"
#include <stdio.h>
Acceptor::Acceptor(const string &ip, unsigned short port)
: _sock()
, _addr(ip, port){}

Acceptor::~Acceptor() = default;

void Acceptor::ready(){
    setReuseAddr();
    setReusePort();
    bind();
    listen();
}

void Acceptor::setReuseAddr(){
    int opt = 1;
    int ret = ::setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if(ret == -1){
        ::perror("setsockopt");
        return;
    }
}

void Acceptor::setReusePort(){
    int opt = 1;
    int ret = ::setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    if(ret == -1){
        ::perror("setsockopt");
        return;
    }
}

void Acceptor::bind(){
    int ret = ::bind(_sock.fd(), (struct sockaddr *)_addr.getInetAddressPtr(), sizeof(struct sockaddr));
    if(ret == -1){
        ::perror("bind");
        return;
    }
}

void Acceptor::listen(){
    int ret = ::listen(_sock.fd(), 128);
    if(ret == -1){
        ::perror("listen");
        return;
    }
}

int Acceptor::accept(){
    int connfd = ::accept(_sock.fd(), nullptr, nullptr);
    if(connfd == -1){
        ::perror("accept");
        return -1;
    }
    return connfd;
}

int Acceptor::fd() const{
    return _sock.fd();
}