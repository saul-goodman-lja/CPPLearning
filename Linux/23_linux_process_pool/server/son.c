#include "header.h"

int sonProcMain(int local_socket)
{
    while(1){

        int net_fd;
        int flag;
        localNetFdRecv(&net_fd, &flag, local_socket);

        printf("son: net_fd %d \n", net_fd);

        if(flag == -1){
            exit(0);
        }

        sendFile(net_fd);

        printf("sendFile done!\n");

        close(net_fd);
        send(local_socket, "1", 1, 0);
    }
    return 0;
}