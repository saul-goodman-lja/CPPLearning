#include <my_header.h>

int main(int argc, char *argv[]){
    
    if(fork() == 0){
        int ret = setsid();
        ERROR_CHECK(ret, -1, "setsid");
        chdir("/");
        umask(0);
        for(int i = 0; i < 1024; i++){
            close(i);
        }
        while(1){
            sleep(1);
        }
    }

    return 0;
}
