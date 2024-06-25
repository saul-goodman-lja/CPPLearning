    #include <my_header.h>

    int main(int argc, char *argv[]){
        

        printf("uid : %d\n", getuid());
        printf("euid : %d\n",geteuid()); 

        while(1){
            sleep(1);
        }

        return 0;
    }
