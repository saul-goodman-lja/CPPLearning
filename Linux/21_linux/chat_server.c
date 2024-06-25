#include <my_header.h>

typedef struct user_cond {
    bool alive;
    time_t slient_time;
} user_cond_t;

static void transmit(int fd, user_cond_t cond[], struct epoll_event *event,
                     int nfds, int epoll_fd) {
    char buf[1024] = {0};
    int alive = 1;
    ssize_t recv_bytes = recv(fd, buf, sizeof(buf), 0);
    if (recv_bytes == 0) {

        cond[fd].alive = false;
        event->data.fd = fd;
        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, event);
        close(fd);
        printf("user %d exit chat! \n", fd);
        alive = 0;
    }
    for (int i = 0; i < nfds; i++) {
        if (cond[i].alive && fd != i) {
            send(i, &alive, sizeof(int), 0);
            send(i, &fd, sizeof(int), 0);
            if (alive == 0) {
                continue;
            }
            send(i, buf, sizeof(buf), 0);
            printf("user %d send to user %d success! \n", fd, i);
        }
    }
}

int main(void) {

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    int reuse = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    char *ip = "172.27.84.98";
    char *port = "8080";

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(atoi(port));

    int ret_bind = bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr));

    listen(socket_fd, 20);

    int epoll_fd = epoll_create(1);
    struct epoll_event event;
    event.events = EPOLLIN;

    event.data.fd = socket_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event);

    event.data.fd = STDIN_FILENO;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event);

    user_cond_t cond[1024];
    memset(&cond, 0, sizeof(cond));

    int nfds = socket_fd + 1;

    struct timeval wait_time;
    wait_time.tv_sec = 1;
    wait_time.tv_usec = 0;

    while (1) {
        bool flag = false;
        struct epoll_event events[10];

        int ready_num = epoll_wait(epoll_fd, events, 10, 1000);

        for (int k = 0; k < ready_num; k++) {

            int cfd = events[k].data.fd;

            if (cfd == socket_fd) {
                int ufd = accept(socket_fd, NULL, NULL);

                cond[ufd].alive = true;

                event.data.fd = ufd;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, ufd, &event);

                if (nfds <= ufd) {
                    nfds = ufd + 1;
                }
                time(&cond[ufd].slient_time);
                printf("new user %d come in chat! \n", ufd);
            }
            if (cfd == STDIN_FILENO) {
                char buf[60] = {0};
                ssize_t read_bytes = read(STDIN_FILENO, buf, sizeof(buf));
                if (read_bytes == 0) {
                    printf("server closed ! \n");
                    flag = true;
                    break;
                }
            }

            for (int i = 0; i < nfds; i++) {
                if (cond[i].alive && cfd == i) {
                    time(&cond[i].slient_time);
                    transmit(i, cond, &event, nfds, epoll_fd);
                }
            }
        }

        for (int i = 0; i < nfds; i++) {
            time_t now_time;
            time(&now_time);
            if (cond[i].alive && now_time - cond[i].slient_time > 30) {
                cond[i].alive = false;
                event.data.fd = i;
                epoll_ctl(epoll_fd, EPOLL_CTL_DEL, i, &event);
                close(i);
                printf("user %d doesn't chat for 30s, forced to exit chat ! \n",
                       i);
            }
        }

        if (flag) {
            break;
        }
    }

    close(socket_fd);
    return 0;
}