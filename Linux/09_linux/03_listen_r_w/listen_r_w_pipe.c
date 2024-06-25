#include<my_header.h>

int main(int argc, char *argv[]){

    ARGS_CHECK(argc, 2);

    int pipe_read_write = open(argv[1], O_RDWR);
    ERROR_CHECK(pipe_read_write, -1, "open pipe read&write");
    
    printf("start \n");

    fd_set set_read, set_write;

    FD_ZERO(&set_read);
    FD_ZERO(&set_write);

    while(1){

        FD_SET(pipe_read_write, &set_read);
        FD_SET(pipe_read_write, &set_write);

        select(pipe_read_write + 1 , &set_read, &set_write, NULL, NULL);

        if(FD_ISSET(pipe_read_write, &set_write)){
            char buf[4096] = {0};
            
            write(pipe_read_write, buf, sizeof(buf));
            printf("4096 bytes has been  written\n");
        }

        if(FD_ISSET(pipe_read_write, &set_read)){
            char buf[1024] = {0};
            read(pipe_read_write, buf, sizeof(buf));
            printf("1024 bytes has been read \n");
        }
    }


    return 0;
}
