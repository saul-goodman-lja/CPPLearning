#include <my_header.h>

typedef struct user_cond {
    bool alive;
    time_t slient_time;
} user_cond_t;

static void transmit(int fd, user_cond_t cond[], fd_set *set, int nfds) {
    char buf[1024] = {0};
    int alive = 1;
    ssize_t recv_bytes = recv(fd, buf, sizeof(buf), 0);
    if (recv_bytes == 0) {

        cond[fd].alive = false;
        FD_CLR(fd, set);
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

    fd_set set;
    FD_ZERO(&set);
    FD_SET(socket_fd, &set);
    FD_SET(STDIN_FILENO, &set);

    user_cond_t cond[1024];
    memset(&cond, 0, sizeof(cond));

    int nfds = socket_fd + 1;

    struct timeval wait_time;
    wait_time.tv_sec = 1;
    wait_time.tv_usec = 0;

    while (1) {

        fd_set temp_set;
        memcpy(&temp_set, &set, sizeof(set));

        select(nfds, &temp_set, NULL, NULL, &wait_time);

        if (FD_ISSET(socket_fd, &temp_set)) {
            int ufd = accept(socket_fd, NULL, NULL);

            cond[ufd].alive = true;

            FD_SET(ufd, &set);

            if (nfds <= ufd) {
                nfds = ufd + 1;
            }
            time(&cond[ufd].slient_time);
            printf("new user %d come in chat! \n", ufd);
        } else if (FD_ISSET(STDIN_FILENO, &temp_set)) {
            char buf[60] = {0};
            ssize_t read_bytes = read(STDIN_FILENO, buf, sizeof(buf));
            if (read_bytes == 0) {
                printf("server closed ! \n");
                break;
            }
        } else {
            for (int i = 0; i < nfds; i++) {
                if (cond[i].alive && FD_ISSET(i, &temp_set)) {
                    time(&cond[i].slient_time);
                    transmit(i, cond, &set, nfds);
                }
            }
        }

        for (int i = 0; i < nfds; i++) {
            time_t now_time;
            time(&now_time);
            if (cond[i].alive && now_time - cond[i].slient_time > 30) {
                cond[i].alive = false;
                FD_CLR(i, &set);
                close(i);
                printf("user %d doesn't chat for 30s, forced to exit chat ! \n", i);
            }
        }
    }

    close(socket_fd);
    return 0;
}