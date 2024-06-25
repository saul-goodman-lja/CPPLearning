#include <my_header.h>

int main(int argc, char *argv[]){

    if(fork() == 0){
        printf("child process exit!\n");
    }else{
        while(1){

        }
    }
        
    return 0;
}
