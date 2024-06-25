#include <my_header.h>

int main(int argc, char *argv[]){

    ARGS_CHECK(argc, 2);

    int pipe_write = open(argv[1], O_WRONLY);
    ERROR_CHECK(pipe_write, -1, "open pipe_write");

    printf("Hello World!\n");
    fflush(stdout);

    int new_stdout = dup2(STDOUT_FILENO, 7);
    ERROR_CHECK(new_stdout, -1, "dup2 new_stdout");

    int send_fd = dup2(pipe_write, STDOUT_FILENO);
    ERROR_CHECK(send_fd, -1, "dup2 send_fd");

    printf("Hello World!\n");
    fflush(stdout);

    int new_fd = dup2(new_stdout, send_fd);
    ERROR_CHECK(new_fd, -1, "dup2 new_fd");

    close(new_stdout);

    printf("Hello World!\n");

    close(pipe_write);

    return 0;
}
