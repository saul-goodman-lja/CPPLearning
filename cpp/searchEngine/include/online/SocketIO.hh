#ifndef _SOCKETIO_HH_
#define _SOCKETIO_HH_
#include <my_header.h>

class SocketIO{
public:
    explicit SocketIO(int fd);
    ~SocketIO();
    int readn(char *buf, int len);
    int readLine(char *buf, int len);
    int readTrain(char *buf, int len); // 根据长度读数据
    int writen(const char *buf, int len);
private:   
    int _fd;
};

#endif