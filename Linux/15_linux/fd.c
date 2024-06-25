#include <my_header.h>

int fd;

void *threadFun(void *arg){

    char buf[60] = "hello, this is a test!\n";
    write(fd, buf, sizeof(buf));
    
    close(fd);

    return NULL;
}

int main(int argc, char *argv[]){

    ARGS_CHECK(argc, 2);

    pthread_t tid;

    fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
    ERROR_CHECK(fd, -1, "open fd");

    int ret = pthread_create(&tid, NULL, threadFun, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    pthread_join(tid, NULL);

    return 0;
}