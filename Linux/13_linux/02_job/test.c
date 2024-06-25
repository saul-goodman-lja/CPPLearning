#define _POSIX_C_SOURCE 200809L
#include <my_header.h>
void func(int num){
    printf("singnal %d\n", num);
}
int main(int argc, char *argv[]){

    sigset_t set, pending_set;
    sigemptyset(&set);
    sigemptyset(&pending_set);

    sigaddset(&set, 2);
    sigprocmask(SIG_BLOCK, &set, NULL);
    
    signal(SIGINT, func);
    printf("sleeping\n");
    sleep(5);

    sigpending(&pending_set);

    if(sigismember(&pending_set, SIGINT)){
        printf("sigint is pending \n");
    }
    
    sigprocmask(SIG_UNBLOCK, &set, NULL);


    return 0;
}
