#include "header.h"

int localNetFdRecv(int *net_fd, int local_socket_fd){

    struct msghdr hdr;
    memset(&hdr, 0, sizeof(hdr));

    struct iovec vec[1];
    int flag = 1;
    vec[0].iov_base = &flag;
    vec[0].iov_len = sizeof(int);

    hdr.msg_iov = vec;
    hdr.msg_iovlen = 1;

    struct cmsghdr *pcmsg = 
        (struct cmsghdr *)malloc(CMSG_LEN(sizeof(int)));

    pcmsg->cmsg_len = CMSG_LEN(sizeof(int));
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;

    hdr.msg_control = pcmsg;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));

    int ret = recvmsg(local_socket_fd, &hdr, 0);
    ERROR_CHECK(ret, -1, "recvmsg");


    void *addr = CMSG_DATA(pcmsg);
    *net_fd = *(int *)addr;

    return 0;
}

int localNetFdSend(int *net_fd, int local_socket_fd){

    struct msghdr hdr;
    memset(&hdr, 0, sizeof(hdr));

    struct iovec vec[1];
    int flag = 1;

    vec[0].iov_base = &flag;
    vec[0].iov_len = sizeof(int);

    hdr.msg_iov = vec;
    hdr.msg_iovlen = 1;

    struct cmsghdr *pcmsg = 
        (struct cmsghdr *)malloc(CMSG_LEN(sizeof(int)));

    pcmsg->cmsg_len = CMSG_LEN(sizeof(int));
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;

    void *addr = CMSG_DATA(pcmsg);
    *(int *)addr = *net_fd;

    hdr.msg_control = pcmsg;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));

    int ret = sendmsg(local_socket_fd, &hdr, 0);
    ERROR_CHECK(ret, -1, "sendmsg");

    return 0;
}