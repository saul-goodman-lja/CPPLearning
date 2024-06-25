#include <my_header.h>

int dirs = 0, files = 0;

void DFS_print(char *dirpath, int width){
    DIR *dirp = opendir(dirpath);
    ERROR_CHECK(dirp,NULL,"opendir");

    struct dirent *pdirent;
    while((pdirent = readdir(dirp)) != NULL){

        if(strcmp(pdirent->d_name, ".") == 0 ||
            strcmp(pdirent->d_name, "..") == 0){
                continue;
        }

        printf("└");
        for(int i = 1; i < width; i++){
            printf("─");
        }

        printf("%s\n", pdirent->d_name);

        if(pdirent->d_type == DT_DIR){
            dirs++;
            char path[1024] = {0};
            sprintf(path, "%s%s%s", dirpath, "/", pdirent->d_name);
            DFS_print(path, width + 4);
        }
        else{
            files++;
        }
    }
    closedir(dirp);
}
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    printf("%s\n",argv[1]);
    DFS_print(argv[1], 4);
    printf("\n%d directories, %d files\n", dirs, files);

    return 0;
}