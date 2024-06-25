#ifndef _HEADER_H
#define _HEADER_H

#include <my_header.h>



int localNetFdRecv(int *net_fd, int local_socket_fd);

int localNetFdSend(int *net_fd, int local_socket_fd);

#endif