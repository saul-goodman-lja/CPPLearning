#include <my_header.h>

int main(void){

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    char *ip = "172.27.84.98";
    char *port = "8080";

    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(atoi(port));
    addr.sin_family = AF_INET;

    int ret = connect(socket_fd, (struct sockaddr *)&addr, sizeof(addr));

    int epoll_fd = epoll_create(1);

    struct epoll_event event;
    event.events = EPOLLIN;

    event.data.fd = socket_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event);

    while(1){

        struct epoll_event events[10];

        int num = epoll_wait(epoll_fd, events, 10, -1);

        for(int i = 0; i < num; i++){
            int cfd = events[i].data.fd;

            if(cfd == socket_fd){
                char buf[60] = {0};
                
                ssize_t recv_bytes = recv(socket_fd, buf, sizeof(buf), 0);
                if(recv_bytes == 0){
                    exit(0);
                }
                printf("recv : %s \n", buf);

            }
        }

    }

    return 0;
}