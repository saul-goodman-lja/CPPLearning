#include <my_header.h>

static int pipe_read;
static int pipe_write;

void func(int num){
    printf("Received signal %d. Exiting...\n", num);
    close(pipe_read);
    close(pipe_write);
    exit(0);
}

int main(int argc, char *argv[]){
    
    
    pipe_read = open("1.pipe", O_RDONLY); 
    ERROR_CHECK(pipe_read, -1, "open");

    pipe_write = open("2.pipe", O_WRONLY);
    ERROR_CHECK(pipe_write, -1, "open");
    
    pid_t pid = getpid();
    char pid_str[80] = {0};
    sprintf (pid_str, "%ld", (long int)pid);
    write(pipe_write, pid_str, strlen(pid_str) + 1);
    
    read(pipe_read, pid_str, sizeof(pid_str));

    pid = (pid_t)strtol(pid_str, NULL, 10);

    signal(10, func);

    fd_set set;

    while(1){
        
        FD_ZERO(&set);
        
        FD_SET(pipe_read, &set);
        FD_SET(STDIN_FILENO, &set);

        select(pipe_write + 1, &set, NULL, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &set)){
            char buf_write[4096] = {0};
            ssize_t ret_write = read(STDIN_FILENO, buf_write, sizeof(buf_write));
            ERROR_CHECK(ret_write, -1, "read");
            if(buf_write[3] == '\0' && buf_write[0] == '1'){
                // printf("my_pid = %u\n",getpid());
                // printf("pid = %u\n",pid);
                kill(pid, 10);
                kill(getpid(), 10);
            }else{
                write(pipe_write, buf_write, sizeof(buf_write));
            }
        }

        if(FD_ISSET(pipe_read, &set)){
            char buf_read[4096] = {0};
            ssize_t ret_read = read(pipe_read, buf_read, sizeof(buf_read));
            ERROR_CHECK(ret_read, -1, "read");
            printf("received: %s", buf_read);
        }

    }

    

    return 0;
}
