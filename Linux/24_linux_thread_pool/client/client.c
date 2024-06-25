#include <my_header.h>

static void recvn(int net_fd, void *buf, int len)
{
    void *buffer = (void *)malloc(4096);
    ERROR_CHECK(buffer, NULL, "malloc");

    off_t cur_size = 0;
    while(cur_size < len)
    {
        memset(buffer, 0, 4096);
        ssize_t recv_bytes = recv(net_fd, buffer, len - cur_size, 0);
        if(recv_bytes == 0){
            fprintf(stderr, "\ndownLoad failed, server closed!\n");
            exit(1);
        }
        ERROR_CHECK(recv_bytes, -1, "recv");
        memcpy(buf + cur_size, buffer, recv_bytes);
        cur_size += recv_bytes;
    }
    free(buffer);
}

static void downloadFile(int net_fd)
{   
    int hash_len;
    recv(net_fd, &hash_len, sizeof(int), MSG_WAITALL);
    char hash[1024] = {0};
    recv(net_fd, hash, hash_len, MSG_WAITALL);

    printf("hash = %s\n", hash);

    int file_name_len;
    recvn(net_fd, &file_name_len, sizeof(int));

    char file_name[4096] = {0};
    recvn(net_fd, file_name, file_name_len);
    printf("file_name = %s\n", file_name);

    off_t file_size;
    recvn(net_fd, &file_size, sizeof(off_t));
    printf("file_size = %ld\n", file_size);
    int file_fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0666);

    off_t offset_bytes;

    char store_name[1024] = {0};
    memcpy(store_name, hash, strlen(hash));
    char *name_cat = ".dat";
    memcpy(store_name + strlen(store_name), name_cat, strlen(name_cat));


    int store_fd = open("1.dat", O_RDONLY);
    if(store_fd == -1){
        off_t x = 0;
        FILE *file = fopen("1.dat", "wb");
        fwrite(&x, sizeof(off_t), 1, file);
        fflush(file);
        fclose(file);
    }else{
        close(store_fd);
    }
    FILE *file = fopen("1.dat", "rb");
    fread(&offset_bytes, sizeof(off_t), 1, file);
    fclose(file);
    printf("offset_bytes = %ld\n", offset_bytes);
    send(net_fd, &offset_bytes, sizeof(off_t), MSG_NOSIGNAL);



    off_t last_update_size = 0;

    char str[101] = {0};
    const char* label = "|/-\\";
    printf("Starting...\n");

    while(offset_bytes < file_size)
    {   
        file = fopen("1.dat", "wb");
        fwrite(&offset_bytes, sizeof(off_t), 1, file);
        fflush(file);
        fclose(file);

        off_t size = (offset_bytes + 4096 < file_size) ? 4096 :
            file_size - offset_bytes;
        ftruncate(file_fd, offset_bytes + size);
        // printf("offsets = %ld \n", offset_bytes + size);

        char *p = (char *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, file_fd, offset_bytes);
        recvn(net_fd, p, size);
        munmap(p, size);

        offset_bytes += size;

        double num = (double)offset_bytes * 100 / file_size - 
                     (double)last_update_size * 100 / file_size;
        static int label_num = 0;
        if(num > 0.1){
            last_update_size = offset_bytes;
            int percent = last_update_size * 100 / file_size;

            memset(str, '-', percent);
            printf("\r\033[95m[%-100s]\033[0m Progress: %.2f%% [%c]", str, 
            (double)last_update_size * 100 / file_size,
            label[label_num++ % 4]);
            fflush(stdout);
            usleep(5000);
        }
    }
    memset(str, '-', 100);
    printf("\r\33[95m[%-100s]\033[0m Progress: %.2f%% [%c]", str, 
        (double)100, label[0]);
    printf("\nDone!\n");


    if(offset_bytes >= file_size){
        off_t x = 0;
        file = fopen("1.dat", "wb");
        fwrite(&x, sizeof(off_t), 1, file);
        fflush(file);
        fclose(file);
        printf("reset to 0 \n");
    }
    off_t file_size1 = lseek(file_fd, 0, SEEK_END);
    printf("file_size = %ld\n", file_size1);
    lseek(file_fd, 0, SEEK_SET);
    close(file_fd);
}

int main(void)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr("172.27.84.98");
    addr.sin_port = htons(atoi("8081"));
    addr.sin_family = AF_INET;

    int ret_connect = connect(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret_connect, -1, "connect");

    socklen_t len = sizeof(addr);
    getsockname(socket_fd, (struct sockaddr *)&addr, &len);
    printf("Server bound to port: %d\n", ntohs(addr.sin_port));

    downloadFile(socket_fd);

    close(socket_fd);

    return 0;
}