#include <my_header.h>
#include <unistd.h>

void *thread1(void *arg){
    
    sleep(2);

    return (void *)1;
}

void *thread2(void *arg){
    
    sleep(2);
    return (void *)2;
}

void *thread3(void *arg){
    
    sleep(2);
    return (void *)3;
}

int main(){

    pthread_t tid1, tid2, tid3;
    int ret1 = pthread_create(&tid1, NULL, thread1, NULL);
    THREAD_ERROR_CHECK(ret1, "pthread_create");

    int ret2 = pthread_create(&tid2, NULL, thread2, NULL);
    THREAD_ERROR_CHECK(ret2, "pthread_create");

    int ret3 = pthread_create(&tid3, NULL, thread3, NULL);
    THREAD_ERROR_CHECK(ret3, "pthread_create");
    
    void *retThread;
    int ret4 = pthread_join(tid1, &retThread);
    THREAD_ERROR_CHECK(ret4, "pthread_join");
    printf("thread 1 return : %d\n", (int *)retThread);

    int ret5 = pthread_join(tid2, &retThread);
    THREAD_ERROR_CHECK(ret5, "pthread_join");
    printf("thread 2 return : %d\n", (int *)retThread);

    int ret6 = pthread_join(tid3, &retThread);
    THREAD_ERROR_CHECK(ret6, "pthread_join");
    printf("thread 3 rerurn : %d\n ", (int *)retThread);

}
