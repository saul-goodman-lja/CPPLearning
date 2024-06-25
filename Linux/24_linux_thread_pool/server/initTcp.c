#include "header.h"

int initSocket(int *socket_fd, char *ip, char *port)
{
    *socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    int reuse = 1;
    setsockopt(*socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    struct sockaddr_in addr;
    // addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_addr.s_addr = inet_addr(INADDR_ANY);
    addr.sin_port = htons(atoi("0"));
    addr.sin_family = AF_INET;

    int bind_ret = bind(*socket_fd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(bind_ret, -1, "bind");

    socklen_t len = sizeof(addr);
    getsockname(*socket_fd, (struct sockaddr *)&addr, &len);
    printf("Server bound to port: %d\n", ntohs(addr.sin_port));

    listen(*socket_fd, 10);

    return *socket_fd;

    
}