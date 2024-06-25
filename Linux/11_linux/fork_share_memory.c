#include <my_header.h>

int main(int argc, char *argv[]){
    
    key_t key_tag = ftok("./init.gdb", 1);

    int shmid = shmget(key_tag, 4096, 0600 | IPC_CREAT);
    ERROR_CHECK(shmid, -1, "shmget");

    int *p = (int *)shmat(shmid, NULL, 0);
    
    *p = 0;

    if(fork() == 0){
        for(int i = 0; i < 10000000; i++){
            p[0]++;
        }
    }else{
        for(int i = 0; i < 10000000; i++){
            p[0]++;
        }
        wait(NULL);
        printf("%d\n", *p);
    }


    return 0;
}
