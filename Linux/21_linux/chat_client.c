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

    int epoll_fd = epoll_create(1);

    struct epoll_event event;
    event.events = EPOLLIN;

    event.data.fd = socket_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event);
    event.data.fd = STDIN_FILENO;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event);

    bool flag = false;

    while (1) {

        struct epoll_event events[10];

        int ready_num = epoll_wait(epoll_fd, events, 10, -1);

        for (int i = 0; i < ready_num; i++) {

            int cfd = events[i].data.fd;

            if (cfd == socket_fd) {

                int alive;
                ssize_t recv_bytes2 = recv(socket_fd, &alive, sizeof(int), 0);

                if (recv_bytes2 == 0) {
                    printf("server closed ! \n");
                    flag = true;
                    break;
                }

                int uid;
                ssize_t recv_bytes1 = recv(socket_fd, &uid, sizeof(int), 0);

                if (alive == 0) {
                    printf("user %d exit chat !\n", uid);
                }

                char buf[1024] = {0};
                ssize_t recv_bytes = recv(socket_fd, buf, sizeof(buf), 0);

                printf("user %d says: %s", uid, buf);
            }
            if (cfd == STDIN_FILENO) {

                char buf[1024] = {0};
                ssize_t read_bytes = read(STDIN_FILENO, buf, sizeof(buf));
                if (read_bytes == 0) {
                    printf("exit chat!\n");
                    flag = true;
                    break;
                }
                send(socket_fd, buf, sizeof(buf), 0);
            }
        }
        if (flag) {
            break;
        }
    }

    close(socket_fd);
    return 0;
}