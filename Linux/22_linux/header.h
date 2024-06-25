#ifndef _HEADER_H
#define _HEADER_H

#include <my_header.h>

enum{
    BUSY,
    FREE,
};

typedef struct work_status_s{
    pid_t pid;
    int status;
    int socket_local_fd;
} work_status_t;

int initPoll(work_status_t *p, int num);

int initSocket(int *socket_fd, char *ip, char *port);

int addEpoll(int epoll_fd, int file_fd);

int sonProcMain(int local_socket);

int toSon(int net_fd, work_status_t *list, int num);

int localNetFdSend(int *net_fd, int local_socket_fd);

int localNetFdRecv(int *net_fd, int local_socket_fd);


#endif