#include <my_header.h>

typedef struct tState {
    pthread_mutex_t lock;
    pthread_cond_t cond;
    bool flag;
} tState;

void *thread1(void *arg) {

    tState *threadState = (tState *)arg;

    pthread_mutex_lock(&threadState->lock);
    printf("A");
    pthread_mutex_unlock(&threadState->lock);

    while(1){
        if(threadState->flag == true){
            pthread_mutex_lock(&threadState->lock);
            pthread_cond_signal(&threadState->cond);
            threadState->flag = false;
            pthread_mutex_unlock(&threadState->lock);
            break;
        }
    }

    pthread_mutex_lock(&threadState->lock);
    threadState->flag = true;
    pthread_cond_wait(&threadState->cond, &threadState->lock);
    printf("C\n");
    pthread_mutex_unlock(&threadState->lock);

    return NULL;
}

void *thread2(void *arg) {

    tState *threadState = (tState *)arg;

    pthread_mutex_lock(&threadState->lock);
    threadState->flag = true;
    pthread_cond_wait(&threadState->cond, &threadState->lock);
    printf("B");
    pthread_mutex_unlock(&threadState->lock);

    while(1){
        if(threadState->flag == true){
            pthread_mutex_lock(&threadState->lock);
            pthread_cond_signal(&threadState->cond);
            threadState->flag = false;
            pthread_mutex_unlock(&threadState->lock);
            break;
        }
    }

    return NULL;
}

int main(int argc, char *argv[]) {

    tState threadState;

    pthread_mutex_init(&threadState.lock, NULL);

    pthread_cond_init(&threadState.cond, NULL);

    threadState.flag = false;

    pthread_t tid1, tid2;

    int ret1 = pthread_create(&tid1, NULL, thread1, &threadState);
    THREAD_ERROR_CHECK(ret1, "pthread_create");

    int ret2 = pthread_create(&tid2, NULL, thread2, &threadState);
    THREAD_ERROR_CHECK(ret2, "pthread_create");

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&threadState.lock);
    pthread_cond_destroy(&threadState.cond);

    return 0;
}