#include "../../include/online/Socket.hh"

Socket::Socket(){
    _fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if(_fd < 0){
        ::perror("socket");
        return;
    }
}

Socket::Socket(int fd)
: _fd(fd){}

Socket::~Socket() = default;

int Socket::fd() const{
    return _fd;
}

void Socket::shutDownWrite(){
    // close write port
    int ret = ::shutdown(_fd, SHUT_WR);
    // if success ret = 0
    if(ret){
        ::perror("shutdown");
        return;
    }
}