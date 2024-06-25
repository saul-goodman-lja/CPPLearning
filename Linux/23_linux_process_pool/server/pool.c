#include "header.h"

int initPoll(work_status_t *p, int num, int pipe_read, int pipe_write){

    int fd[3] = {0};

    for(int i = 0; i < num; i++){
        int socket_fd[2];
        socketpair(AF_LOCAL, SOCK_STREAM, 0, socket_fd);

        int pid = fork();

        if(pid == 0){
            
            // close(socket_fd[1]);
            // close(pipe_read);
            // close(pipe_write);
            // int temp = i;
            // while(temp > 0){
            //     close(p[temp - 1].socket_local_fd);
            //     temp--;
            // }
            sonProcMain(socket_fd[0]);

        }else{
            p[i].pid = pid;
            p[i].status = FREE;
            close(socket_fd[0]);
            p[i].socket_local_fd = socket_fd[1];
        }

    }

    return 0;
}

int toSon(int net_fd, work_status_t *list, int num){
    
    for(int i = 0; i < num; i++){

        if(list[i].status == FREE){
            localNetFdSend(&net_fd, 0, list[i].socket_local_fd);
            list[i].status = BUSY;
            printf("child process %d start running !\n", list[i].pid);
            break;
        }
    }

    return 0;
}