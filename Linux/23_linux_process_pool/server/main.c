#include "header.h"

int pipe_fd[2];
void signal_func(int num){
    write(pipe_fd[1], "2", 1);
}

int main(void){

    pipe(pipe_fd);

    signal(2, signal_func);

    work_status_t workArray[3];
    initPoll(workArray, 3, pipe_fd[0], pipe_fd[1]);

    int socket_fd;
    initSocket(&socket_fd, "172.27.84.98", "8080");

    int epoll_fd = epoll_create(1);
    addEpoll(epoll_fd, socket_fd);

    addEpoll(epoll_fd, pipe_fd[0]);

    for(int i = 0; i < 3; i++){
        addEpoll(epoll_fd, workArray[i].socket_local_fd);
    }

    while(1){
        struct epoll_event events[10];
        int num = epoll_wait(epoll_fd, events, 10, -1);

        for(int i = 0; i < num; i++){
            int cfd = events[i].data.fd;

            if(cfd == pipe_fd[0]){
                char buf[60] = {0};
                read(pipe_fd[0], buf, sizeof(buf));
                
                for(int k = 0; k < 3; k++){
                    int temp = 1;
                    localNetFdSend(&temp, -1, workArray[k].socket_local_fd);
                }

                for(int k = 0; k < 3; k++){
                    wait(NULL);
                }

                printf("All child process exit!\n");

                exit(0);
            }
            else if(cfd == socket_fd){
                int net_fd = accept(socket_fd, NULL, NULL);
                printf("new user %d connect!\n", net_fd);
                toSon(net_fd, workArray, 3);
                close(net_fd);
            }else {
                char buf[60] = {0};
                recv(cfd, buf, sizeof(buf), 0);

                for(int k = 0; k < 3; k++){
                    if(workArray[i].socket_local_fd == cfd){
                        workArray[k].status = FREE;
                        printf("child process %d finish work! \n", workArray[i].pid);
                        break;
                    }
                }
            }
        }
    }

    close(socket_fd);
    return 0;
}