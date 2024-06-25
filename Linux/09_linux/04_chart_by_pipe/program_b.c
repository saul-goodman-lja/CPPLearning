#include <my_header.h>

int main(int argc, char *argv[]){

    ARGS_CHECK(argc, 2);

    int pipe_read = open(argv[1], O_RDONLY);
    ERROR_CHECK(pipe_read, -1, "open pipe_read");

    fd_set set;

    FD_ZERO(&set);
    
    while(1){
        FD_SET(pipe_read, &set);
        
        select(pipe_read + 1, &set, NULL, NULL, NULL);

        if(FD_ISSET(pipe_read, &set)){

            char buf[60] = {0};
            read(pipe_read, buf,sizeof(buf));

            write(STDOUT_FILENO, buf, sizeof(buf));
            break;
        }
    }

    close(pipe_read);

    return 0;
}