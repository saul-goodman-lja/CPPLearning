#include <my_header.h>

long long current_time_millis() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); // 获取当前时间
    return (long long)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000; // 转换为毫秒
}

int main(int argc, char *argv[]){

    long long start = current_time_millis();
    ARGS_CHECK(argc,3);
    int fd_resourse = open(argv[1],O_RDONLY);
    ERROR_CHECK(fd_resourse,-1,"open_resourse");
    int fd_destination = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, 0666);
    ERROR_CHECK(fd_destination, -1, "open_destination");

    char buffer[2] = {0};

    ssize_t sret;

    while((sret = read(fd_resourse, buffer, sizeof(buffer))) > 0){
        write(fd_destination, buffer, sret);
    }

    close(fd_destination);
    close(fd_resourse);

    long long end = current_time_millis();
    printf("%lld\n",(end -start));

    return 0;
}