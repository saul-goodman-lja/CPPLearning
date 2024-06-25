#include <my_header.h>

int main(void) {

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    char *ip = "172.27.84.98";
    char *port = "8080";

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(atoi(port));

    int ret_connet = connect(socket_fd, (struct sockaddr *)&addr, sizeof(addr));

    fd_set set;
    FD_ZERO(&set);

    while (1) {

        FD_SET(socket_fd, &set);
        FD_SET(STDIN_FILENO, &set);
        select(socket_fd + 1, &set, NULL, NULL, NULL);

        if (FD_ISSET(socket_fd, &set)) {

            int alive;
            ssize_t recv_bytes2 = recv(socket_fd, &alive, sizeof(int), 0);

            if (recv_bytes2 == 0) {
                printf("server closed ! \n");
                break;
            }

            int uid;
            ssize_t recv_bytes1 = recv(socket_fd, &uid, sizeof(int), 0);

            if(alive == 0){
                printf("user %d exit chat !\n", uid);
            }

            char buf[1024] = {0};
            ssize_t recv_bytes = recv(socket_fd, buf, sizeof(buf), 0);

            printf("user %d says: %s", uid, buf);

        } else if (FD_ISSET(STDIN_FILENO, &set)) {

            char buf[1024] = {0};
            ssize_t read_bytes = read(STDIN_FILENO, buf, sizeof(buf));
            if (read_bytes == 0) {
                printf("exit chat!\n");
                break;
            }
            send(socket_fd, buf, sizeof(buf), 0);
        }
    }

    close(socket_fd);
    return 0;
}