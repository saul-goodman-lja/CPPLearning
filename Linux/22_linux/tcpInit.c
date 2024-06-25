#include "header.h"

int initSocket(int *socket_fd, char *ip, char *port){

    *socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(atoi(port));
    addr.sin_family = AF_INET;

    int ret_bind = bind(*socket_fd, (struct sockaddr *)&addr, sizeof(addr));

    listen(*socket_fd, 10);

    return 0;
}