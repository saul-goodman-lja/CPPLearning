#include <my_header.h>

void recvn(int net_fd, void *buf, int length)
{   
    void *buffer = (void *)malloc(4096);
    int len = 0;
    ssize_t recv_bytes = 0;
    while(recv_bytes < length){
        memset(buffer, 0, 4096);
        len = recv(net_fd, buffer, length - recv_bytes, 0);
        if(len <= 0){
            break;
        }
        memcpy(buf + recv_bytes, buffer, len);
        recv_bytes += len;
    }

    free(buffer);
}


void downloadFile(int net_fd, int socket_fd)
{
    // get file_name
    

    int file_name_len;
    char file_name[1024] = {0};
    recvn(net_fd, &file_name_len, sizeof(int));
    recvn(net_fd, file_name, file_name_len);
    
    off_t file_size;
    recvn(net_fd, &file_size, sizeof(off_t));
    printf("file_size = %ld\n", file_size);

    int file_fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
    ftruncate(file_fd, file_size);

    off_t offset_bytes = 0;
    off_t last_update_size = 0;
    printf("Starting...\n");


    char str[101] = {0};
    const char* label = "|/-\\";
    while(offset_bytes < file_size){
        off_t size = (offset_bytes + 4096 < file_size) ? 4096 :
            file_size - offset_bytes;
        
        char *p = (char *)mmap(NULL, size, PROT_READ | PROT_WRITE,
         MAP_SHARED, file_fd, offset_bytes);
        recvn(net_fd, p, size);
        munmap(p, size);

        offset_bytes += size;

        double num = (double)offset_bytes * 100 / file_size -
                     (double)last_update_size * 100 / file_size;
        if(num > 1){
            last_update_size = offset_bytes;
            int n = offset_bytes * 100 / file_size;
            memset(str, '-', n);
            printf("\r\033[95m[%-100s]\033[0m Progress: %.2f%% [%c]", str,
                (double)last_update_size * 100 / file_size, 
                label[n % 4]);
            fflush(stdout);
            usleep(50000);
        }
    }
    memset(str, '-', 100);
    printf("\r\033[95m[%-100s]\033[0m Progress: %.2f%% [%c]", str, (double)100, label[0]);
    printf("\nDone!\n");

    close(file_fd);
}

int main(void){

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    char *ip = "172.27.84.98";
    char *port = "8080";

    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(atoi(port));
    addr.sin_family = AF_INET;

    int ret = connect(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "connect");

    downloadFile(socket_fd, socket_fd);

    close(socket_fd);

    return 0;
}