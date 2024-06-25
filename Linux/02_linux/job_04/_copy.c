#include <my_header.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

    FILE *fp = fopen("test.txt","r");
    ERROR_CHECK(fp,NULL,"fopen");

    FILE *dest = fopen("dest.txt","w");
    if(dest == NULL){
        fclose(fp);
        perror("fopen");
        exit(1);
    }
    
    char str[1024];
    while(fgets(str,sizeof(str), fp) != NULL){
        fputs(str, dest);
    }
    
    fclose(dest);
    fclose(fp);
    return 0;
}

