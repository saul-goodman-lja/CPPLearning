#include "header.h"

int addEpoll(int epoll_fd, int file_fd)
{
    struct epoll_event event;
    event.events = EPOLLIN;

    event.data.fd = file_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, file_fd, &event);
    return 0;
}