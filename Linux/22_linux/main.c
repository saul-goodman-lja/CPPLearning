#include "header.h"

int main(void){

    work_status_t workArray[3];
    initPoll(workArray, 3);

    int socket_fd;
    initSocket(&socket_fd, "172.27.84.98", "8080");

    int epoll_fd = epoll_create(1);
    addEpoll(epoll_fd, socket_fd);

    while(1){
        struct epoll_event events[10];
        int num = epoll_wait(epoll_fd, events, 10, -1);

        for(int i = 0; i < num; i++){
            int cfd = events[i].data.fd;
            if(cfd == socket_fd){
                int net_fd = accept(socket_fd, NULL, NULL);
                toSon(net_fd, workArray, 3);
            }
        }
    }

    close(socket_fd);
    return 0;
}