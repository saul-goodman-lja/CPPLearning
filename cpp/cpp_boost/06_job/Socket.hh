#ifndef _SOCKET_HH_
#define _SOCKET_HH_
#include <my_header.h>

class Socket{
public:
    Socket();
    explicit Socket(int);
    ~Socket();
    int fd() const;
    void shutDownWrite();
private:
    int _fd;
};

#endif