#ifndef _SOCKET_HH_
#define _SOCKET_HH_
#include <my_header.h>
#include "NonCopyable.hh"

class Socket : public NonCopyable{
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