#include <my_header.h>

long long current_time_millis() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); // 获取当前时间
    return (long long)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000; // 转换为毫秒
}

int main(int argc, char *argv[]){

    long long start = current_time_millis();
    ARGS_CHECK(argc,3);
    FILE *fp_resource = fopen(argv[1],"r");
    ERROR_CHECK(fp_resource,NULL,"fopen resource")
    FILE *fp_destination = fopen(argv[2], "w");
    if(fp_destination == NULL){
        fclose(fp_resource);
        perror("fopen destination");
        exit(1);
    }

    char str[2];
    while(fgets(str, sizeof(str), fp_resource) != NULL){
        fputs(str,fp_destination);
    }

    fclose(fp_destination);
    fclose(fp_resource);
    long long end = current_time_millis();

    printf("%lld\n", (end -start));
    return 0;
}