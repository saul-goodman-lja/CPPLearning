#include <my_header.h>

int main(int argc, char *argv[]){
    
    if(fork() == 0){

        while(1){

        }

    }else{
        printf("parent process exit!\n");
    }


    return 0;
}
