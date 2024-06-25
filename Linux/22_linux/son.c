#include "header.h"

int sonProcMain(int local_socket)
{
    while(1){

        int net_fd;
        localNetFdRecv(&net_fd, local_socket);

        printf("son: net_fd %d \n", net_fd);

        send(net_fd, "hello", 5, 0);

    }
    return 0;
}