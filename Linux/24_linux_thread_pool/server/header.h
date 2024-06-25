#ifndef _HEADER_H
#define _HEADER_H

#include <my_header.h>
#include "queue.h"

typedef struct pool_status{
    pthread_t *tid;
    
    int tnum;
    
    Queue *queue;

    pthread_mutex_t lock;
    pthread_cond_t cond;

    bool is_exit;

} pool_thread;

int initPool(pool_thread *, const int);

// socket_fd, ip, port
int initSocket(int *, char *, char *);

void addEpoll(const int, const int);

void *threadMain(void *);

int sendFile(const int);

#endif