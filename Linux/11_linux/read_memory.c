#include <my_header.h>

int main(int argc, char *argv[]){
    
    key_t key_tag = ftok("./Makefile", 1);

    int shmid = shmget(key_tag, 4096, 0600 | IPC_CREAT);
    ERROR_CHECK(shmid, -1, "shmget");

    char *p = (char *)shmat(shmid, NULL, 0);

    printf("%s",p);

    shmdt(p);

    shmctl(shmid, IPC_RMID, NULL);


    return 0;
}
