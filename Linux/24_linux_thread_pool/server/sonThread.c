#include "header.h"

// void cleanLock(void *arg)
// {
//     pool_thread *pool = (pool_thread *)arg;

//     pthread_mutex_unlock(&pool->lock);
// }

void *threadMain(void * arg)
{
    pool_thread *pool = (pool_thread *)arg;

    int net_fd;

    while(1)
    {
        pthread_mutex_lock(&pool->lock);
        // printf("thread %lu locked!\n", pthread_self());
        // pthread_cleanup_push(cleanLock, pool);

        while(pool->queue->size == 0 && pool->is_exit == false){
            // printf("thread %lu unlocked!\n\n", pthread_self());
            pthread_cond_wait(&pool->cond, &pool->lock);
            // printf("thread %lu locked!\n", pthread_self());
        }

        if(pool->is_exit == true){
            pthread_mutex_unlock(&pool->lock);
            // printf("thread %lu unlocked!\n", pthread_self());
            printf("thread %lu exit!\n\n", pthread_self());

            pthread_exit(NULL);
        }
        
        net_fd = pool->queue->head->net_fd;
        poll(pool->queue);

        pthread_mutex_unlock(&pool->lock);
        // printf("thread %lu unlocked!\n\n", pthread_self());
        // pthread_cleanup_pop(1);

        printf("thread %lu start to sendfile...\n", pthread_self());


        int ret = sendFile(net_fd);
        if(ret != -1){
            printf("\nthread %lu finish sendfile! \n", pthread_self());
        }
        close(net_fd);

        // if(pool->is_exit == true){
        //     printf("thread %lu exit!\n\n", pthread_self());
        //     // pthread_cond_signal(&pool->cond);
        //     pthread_exit(NULL);
        // }
    }
    return NULL;
}