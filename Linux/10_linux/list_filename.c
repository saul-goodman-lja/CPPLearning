#include <my_header.h>

int main(int argc, char *argv[]){
    
    DIR *dirp = opendir(".");
    ERROR_CHECK(dirp, NULL, "opendir .");

    struct dirent *pdirent;
    while((pdirent = readdir(dirp)) != NULL){
        printf("%s\n",pdirent->d_name);
    }

    closedir(dirp);
    return 0;
}
