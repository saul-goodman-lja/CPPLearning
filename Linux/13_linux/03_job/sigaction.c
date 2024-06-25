#define _POSIX_C_SOURCE 200809L
#include <my_header.h>
void func(int num){
    printf("singnal %d is handling \n", num);
    sigset_t pending_set;
    sigemptyset(&pending_set);

    sleep(5);

    sigpending(&pending_set);

    if(sigismember(&pending_set, SIGQUIT)){
        printf("SIGQUIT is pending \n");
    }

    printf("singnal %d over \n", num);
}
int main(int argc, char *argv[]){

    struct sigaction act, old;
    memset(&act, 0, sizeof(act));
    memset(&old, 0, sizeof(old));

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, 3);

    act.sa_handler = func;
    act.sa_flags = SA_RESTART;
    act.sa_mask = mask;

    sigaction(2, &act, &old);
    char buf[60] = {0};
    int ret = read(STDIN_FILENO, buf, sizeof(buf));

    printf("buf = %s",buf);

    return 0;
}
