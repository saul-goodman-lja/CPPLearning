#include <my_header.h>

int main(int argc, char *argv[]){

    if(fork() == 0){
        char *args[] = {"./list_filename",(char *)0};
        execv("/home/lja/user/CppLearning/Linux/10_linux/list_filename",args);

    }else{
        wait(NULL);
    }

    return 0;
}
