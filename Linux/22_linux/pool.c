#include "header.h"

int initPoll(work_status_t *p, int num){


    for(int i = 0; i < num; i++){
        int socket_fd[2];
        socketpair(AF_LOCAL, SOCK_STREAM, 0, socket_fd);

        int pid = fork();

        if(pid == 0){

            close(socket_fd[1]);


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
            localNetFdSend(&net_fd, list[i].socket_local_fd);
            list[i].status = BUSY;
            break;
        }
    }

    return 0;
}