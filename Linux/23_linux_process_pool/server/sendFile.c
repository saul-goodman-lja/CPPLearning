#include "header.h"

typedef struct trans{
    int len;
    char name[4096];
} trans_t;

int sendFile(int net_fd){

    char *file_name = "tcp_ip.pdf";
    int file_fd = open(file_name, O_RDWR);

    trans_t trans;
    memset(&trans, 0, sizeof(trans));
    trans.len = strlen(file_name);
    memcpy(trans.name, file_name, trans.len);
    send(net_fd, &trans, sizeof(int) + trans.len, MSG_NOSIGNAL);

    off_t file_size = lseek(file_fd, 0, SEEK_END);
    lseek(file_fd, 0, SEEK_SET);
    send(net_fd, &file_size, sizeof(off_t), MSG_NOSIGNAL);
    printf("file_size = %ld \n", file_size);

    // sleep(10);

    off_t offset_bytes = 0;
    while(offset_bytes < file_size){

        off_t size = (offset_bytes + 4096 < file_size) ? 4096 :
            file_size - offset_bytes;

        sendfile(net_fd, file_fd, &offset_bytes, size);
        
        // offset_bytes += size;

    }

    close(file_fd);
    return 0;
}