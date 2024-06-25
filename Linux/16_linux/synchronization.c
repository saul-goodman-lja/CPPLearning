#include <my_header.h>

pthread_mutex_t lock;
pthread_cond_t cond;

void *thread1(void *arg) {

    pthread_mutex_lock(&lock);
    pthread_cond_wait(&cond,    &lock);
    printf("Before B!\n");
    pthread_mutex_unlock(&lock);

    sleep(3);

    pthread_mutex_lock(&lock);
    printf("After B!\n");
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_mutex_init(&lock, NULL);

    pthread_cond_init(&cond, NULL);

    pthread_t tid;
    int ret = pthread_create(&tid, NULL, thread1, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    pthread_mutex_lock(&lock);
    printf("Before A!\n");
    pthread_mutex_unlock(&lock);

    sleep(3);

    pthread_mutex_lock(&lock);
    printf("After A!\n");
    pthread_mutex_unlock(&lock);

    pthread_cond_signal(&cond);

    pthread_join(tid, NULL);
    
    pthread_mutex_destroy(&lock);

    pthread_cond_destroy(&cond);

    return 0;
}
