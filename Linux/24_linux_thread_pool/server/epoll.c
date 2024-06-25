#include "header.h"

void addEpoll(const int epoll_fd, const int fd)
{
    struct epoll_event event;
    event.events = EPOLLIN;

    event.data.fd = fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
    
}