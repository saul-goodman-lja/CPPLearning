#define _POSIX_C_SOURCE 200809L
#include <my_header.h>
void func(int num){
    printf("singnal %d is handling \n", num);

    printf("singnal %d over \n", num);
}
int main(int argc, char *argv[]){

    sigset_t set,pendingSet;

    signal(2, func);

    sigemptyset(&set);
    sigaddset(&set, 2);
    sigprocmask(SIG_BLOCK, &set, NULL);

    kill(getpid(), SIGINT);
    kill(getpid(), SIGINT);
    kill(getpid(), SIGINT);

    sigpending(&pendingSet);

    for (int i = 1; i < SIGRTMAX; i++) {
        if (sigismember(&pendingSet, i)) {
            printf("Signal %d is pending\n", i);
        }
    }

    sigprocmask(SIG_UNBLOCK, &set, NULL);

    return 0;
}
