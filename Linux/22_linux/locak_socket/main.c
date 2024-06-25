#include "header.h"

int main(void){

    int socket_fd[2];
    socketpair(AF_LOCAL, SOCK_STREAM, 0, socket_fd);

    if(fork() == 0){
        // child process
        close(socket_fd[0]);

        int fd = open("1.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);

        localNetFdSend(&fd, socket_fd[1]);

        int exit_fd;
 
        localNetFdRecv(&exit_fd, socket_fd[1]);
        close(fd);
        printf("child process exit!\n");

    }else{
        // parent process
        close(socket_fd[1]);
        int fd;
        localNetFdRecv(&fd, socket_fd[0]);
        write(fd, "hello world!", 12);
        printf("write \"%s\" success! \n","hello world!");
        int exit_fd = 0;
        localNetFdSend(&exit_fd, socket_fd[0]);
        wait(NULL);
        printf("child process exit!\n");
    }

    return 0;
}