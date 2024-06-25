#include <my_header.h>

void stdout_to_file(char *args){
    int fd = open(args, O_RDWR | O_CREAT | O_TRUNC, 0666);
    ERROR_CHECK(fd, -1, "open");

    close(STDOUT_FILENO);

    int fd_cp = dup(fd);
    printf("fd = %d\n", fd);
    printf("fd_cp = %d\n", fd_cp);
    fflush(stdout);
    close(fd);
    close(fd_cp);
}

void stdin_to_file(char *args){
    int fd = open(args, O_RDONLY);
    ERROR_CHECK(fd, -1, "open");

    int fd_cp = dup2(fd,STDIN_FILENO);
    ERROR_CHECK(fd_cp, -1, "dup2");

    char str[1024];
    scanf("%s",str);
    printf("file contents: %s\n", str);

    close(fd);
    close(fd_cp);
}

void jump_over(char *args){

    // printf("terminal 1\n");
    int old_fd = open(args, O_RDWR | O_CREAT | O_TRUNC, 0666);
    ERROR_CHECK(old_fd, -1, "open old_fd");

    int new_fd = dup2(STDOUT_FILENO, 7);
    ERROR_CHECK(new_fd, -1, "dup2 newfd");

    // orient file
    close(1);
    int fd_cp = dup(old_fd);
    ERROR_CHECK(fd_cp, -1, "dup oldfd");
    // printf("file 1\n");

    // orient stdout
    int stdout_fd = dup2(new_fd,fd_cp);
    // printf("terminal 2\n");

    // orient file
    close(stdout_fd);
    int new_stdout_fd = dup(old_fd);
    // printf("file 2\n");

    close(old_fd);
    close(new_fd);
    close(new_stdout_fd);
}

void stderror_to_log(char *args){
    int fd = open(args, O_WRONLY);
    ERROR_CHECK(fd, -1, "open fd");

    close(STDERR_FILENO);
    int fd_cp = dup(fd);
    ERROR_CHECK(fd_cp, -1, "open fd_cp");

    fprintf(stderr,"this is a error!!!\n");

    close(fd);
    close(fd_cp);
}

int main(int argc, char *argv[]){

    ARGS_CHECK(argc, 2);
    // stdout_to_file(argv[1]);
    // stdin_to_file(argv[1]);
    jump_over(argv[1]);
    //stderror_to_log(argv[1]);


    return 0;
}
