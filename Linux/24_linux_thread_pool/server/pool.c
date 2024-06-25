#include "header.h"

int initPool(pool_thread *pool, const int num)
{
    pool->tid = calloc(num, sizeof(pthread_t));
    pool->tnum = num;
    pool->is_exit = false;
    pool->queue = calloc(1, sizeof(Queue));

    pthread_mutex_init(&pool->lock, NULL);
    pthread_cond_init(&pool->cond, NULL);

    for(int i = 0; i < num; i++)
    {
        pthread_create(&pool->tid[i], NULL, threadMain, pool);
    }
    
    return 0;
}