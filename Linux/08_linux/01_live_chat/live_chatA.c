#include<my_header.h>

int main(int argc, char *argv[]){
        
    ARGS_CHECK(argc, 1);

    int fd_read = open("1.pipe",O_RDONLY);
    ERROR_CHECK(fd_read, -1, "open read");
    int fd_write = open("2.pipe", O_WRONLY);
    ERROR_CHECK(fd_write, -1, "open write");
    
    printf("start chat: \n");

    fd_set set;

    time_t time_cur = time(NULL);
    time_t time_a_send = time(NULL);
    
    struct timeval time_val;

    FD_ZERO(&set);

    while(1){
    
        FD_SET(STDIN_FILENO, &set);
        FD_SET(fd_read, &set);

        time_val.tv_sec = 1;
        time_val.tv_usec = 0;

        select(fd_write + 1, &set, NULL, NULL, &time_val);

        time_cur = time(NULL);

        if(FD_ISSET(STDIN_FILENO, &set)){
            char buf[60] = {0};
            int rst = read(STDIN_FILENO, buf, sizeof(buf));
            if(rst == 0){
                break;
            }
            write(fd_write, buf, sizeof(buf));
        }

        if(FD_ISSET(fd_read, &set)){
            char buf[60] = {0};
            int ret = read(fd_read, buf, sizeof(buf));
            if(ret == 0){
                printf("对方关闭连接\n");
                break;
            }
            printf("B: %s",buf);

            time_a_send = time(NULL);
        }

        if(time_cur - time_a_send >= 10){
            printf("对方10秒未发送消息\n");
            break;
        }
    }
    
    close(fd_write);
    close(fd_read);

    return 0;
}

