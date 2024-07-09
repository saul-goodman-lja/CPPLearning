#ifndef _INETADDRESS_HH_
#define _INETADDRESS_HH_

#include <my_header.h>
#include <string>

using std::string;

class InetAddress{
public:
    InetAddress(const string &ip, unsigned short port);
    InetAddress(const struct sockaddr_in & addr);
    ~InetAddress();
    string ip() const;
    unsigned short port() const;
    const struct sockaddr_in * getInetAddressPtr() const;

private:
    struct sockaddr_in _addr;
};

#endif