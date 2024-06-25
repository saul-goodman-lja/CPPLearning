#include "header.h"

typedef struct file_type{

    int len;
    char name[4096];

} fileType;

int sendFile(const int net_fd)
{   
    char buf[1024] = {0};
    FILE *pipe = popen("sha1sum /home/lja/user/CppLearning/Linux/24_linux_thread_pool/server/tcp_ip.pdf", "r");
    //FILE *pipe = popen("md5sum file.txt", "r");
    fread(buf,1, sizeof(buf), pipe);

    int len = strlen(buf);
    char *name = "  /home/lja/user/CppLearning/Linux/24_linux_thread_pool/server/tcp_ip.pdf";
    memset(buf + len - strlen(name) - 1, 0, strlen(name));

    pclose(pipe);

    printf("hash = %s\n", buf);


    int hash_len = strlen(buf);
    send(net_fd, &hash_len, sizeof(int), MSG_NOSIGNAL);
    send(net_fd, buf, hash_len, MSG_NOSIGNAL);

    char *file_name = "tcp_ip.pdf";
    fileType newFile;
    memset(&newFile, 0, sizeof(newFile));

    newFile.len = strlen(file_name);
    memcpy(newFile.name, file_name, strlen(file_name));

    int ret_send_name = send(net_fd, &newFile, sizeof(int) + newFile.len, MSG_NOSIGNAL);
    ERROR_CHECK(ret_send_name, -1, "send");

    int file_fd = open(file_name, O_RDWR);
    off_t file_size = lseek(file_fd, 0, SEEK_END);
    printf("file_size = %ld\n", file_size);
    lseek(file_fd, 0, SEEK_SET);
    ssize_t send_name_bytes = send(net_fd, &file_size, sizeof(off_t), MSG_NOSIGNAL);
    ERROR_CHECK(send_name_bytes, -1, "send");

    off_t offsets;
    recv(net_fd, &offsets, sizeof(off_t), MSG_WAITALL);
    printf("recv offsets = %ld\n", offsets);

    ssize_t send_bytes = sendfile(net_fd, file_fd, &offsets, file_size);
    ERROR_CHECK(send_bytes, -1, "sendfile");
    printf("send = %ld\n", offsets);

    close(file_fd);
    if(send_bytes != file_size){
        fprintf(stderr, "thread %lu send failed, client close connection!\n", pthread_self());
        return -1;
    }

    return 0;
}