#ifndef _ACCEPTOR_HH_
#define _ACCEPTOR_HH_

#include "InetAddress.hh"
#include "Socket.hh"

class Acceptor{
public:
    Acceptor(const string &ip, unsigned short port);
    ~Acceptor();
    void ready();
private:
    void setReuseAddr();
    void setReusePort();
    void bind();
    void listen();
public:
    int accept();
    int fd() const;
private:
    Socket _sock;
    InetAddress _addr;
};

#endif