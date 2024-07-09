#include <my_header.h>
#include <poll.h>

#define SERV_PORT 8888
#define OPEN_MAX 1024
int main(void){

    int i, j, n, maxi;
    int nready, ret;
    int listenfd, connfd, sockfd;
    char buf[BUFSIZ], str[INET_ADDRSTRLEN];
    struct sockaddr_in serv_addr, clie_addr;
    socklen_t clie_addr_len;
    struct pollfd client[OPEN_MAX];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        perror("socket error");
        exit(-1);
    }
    

    return 0;
}