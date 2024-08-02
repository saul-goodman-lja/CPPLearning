#include "../../include/online/InetAddress.hh"

InetAddress::InetAddress(const string &ip, unsigned short port){
    ::bzero(&_addr, sizeof(struct sockaddr_in));
    _addr.sin_family = AF_INET;
    // _addr.sin_addr.s_addr = inet_addr(ip.c_str());
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);
    _addr.sin_port = htons(port);
}

InetAddress::InetAddress(const struct sockaddr_in & addr)
: _addr(addr){}

InetAddress::~InetAddress() = default;

string InetAddress::ip() const{
    //从网络字节序转换为本机字节序
    return string(::inet_ntoa(_addr.sin_addr));
}

unsigned short InetAddress::port() const{
    //从网络字节序转换为本机字节序
    return ::ntohs(_addr.sin_port);
}

const struct sockaddr_in *InetAddress::getInetAddressPtr() const{
    return &_addr;
}