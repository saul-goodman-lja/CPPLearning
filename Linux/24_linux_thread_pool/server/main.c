#include "header.h"
#define PIPE_READ 0
#define PIPE_WRITE 1

static int pipe_fd[2];

static void signal_func()
{
    printf("\ncapture signal SIGINT\n");
    write(pipe_fd[PIPE_WRITE], "1", 1);
}

static void free_func(pool_thread *pthreads){
    free(pthreads->tid);
    Node *cur = pthreads->queue->tail;
    while(cur != NULL){
        Node *temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(pthreads);
}

int main(void)
{
    pipe(pipe_fd);
    
    if(fork() != 0){
        //parent process
        // TODO
        signal(SIGINT, signal_func);

        wait(NULL);

        close(pipe_fd[PIPE_READ]);
        close(pipe_fd[PIPE_WRITE]);
        exit(0);
    }

    // child process
    // TODO
    setpgid(0, 0);
    // setsid();
    close(pipe_fd[PIPE_WRITE]);

    pool_thread *pthreads = malloc(sizeof(pool_thread));

    initPool(pthreads, 3);

    int socket_fd;
    initSocket(&socket_fd, "172.27.84.98", "8081");

    int epoll_fd = epoll_create(1);
    addEpoll(epoll_fd, socket_fd);

    addEpoll(epoll_fd, pipe_fd[PIPE_READ]);

    while(1){

        struct epoll_event events[10];

        int num = epoll_wait(epoll_fd, events, 10, -1);

        for(int i = 0; i < num; i++){

            int cfd = events[i].data.fd;

            if(cfd == pipe_fd[PIPE_READ]){
                char buf[60] = {0};
                read(pipe_fd[PIPE_READ], buf, sizeof(buf));

                // printf("thread %lu locked!\n", pthread_self());
                pthread_mutex_lock(&pthreads->lock);
                printf("prepare to exit...\n");
                pthreads->is_exit = true;
                pthread_cond_broadcast(&pthreads->cond);
                pthread_mutex_unlock(&pthreads->lock);
                // printf("thread %lu unlocked!\n\n", pthread_self());

                // for(int j = 0; j < pthreads->tnum; j++){
                //     pthread_cancel(pthreads->tid[j]);
                // }
                for(int j = 0; j < pthreads->tnum; j++){
                    pthread_join(pthreads->tid[j], NULL);
                    // printf("thread %lu exit!\n", pthreads->tid[j]);
                }
                printf("main thread exit! \n");
                close(pipe_fd[PIPE_READ]);
                close(socket_fd);
                close(epoll_fd);
                free_func(pthreads);
                exit(0);
            }
            else if(cfd == socket_fd){
                int net_fd = accept(socket_fd, NULL, NULL);

                // printf("thread %lu locked!\n", pthread_self());
                pthread_mutex_lock(&pthreads->lock);
                offer(pthreads->queue, net_fd);
                pthread_cond_signal(&pthreads->cond);
                pthread_mutex_unlock(&pthreads->lock);
                // printf("thread %lu unlocked!\n\n", pthread_self());
                
            }

        }

    }   

    return 0;
}