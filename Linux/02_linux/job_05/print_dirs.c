#include <my_header.h>

int main(int argc, char *argv[]){

    ARGS_CHECK(argc,2);
    DIR * dirp = opendir(argv[1]);

    ERROR_CHECK(dirp,NULL,"opendir");
    struct dirent * pdirent;

    while((pdirent = readdir(dirp)) != NULL){
        printf("inode num = %lu, offset = %lu, reclen = %hu, type = %u, name = %s\n",
               pdirent->d_ino, 
               pdirent->d_off,      
               pdirent->d_reclen,   
               pdirent->d_type,     
               pdirent->d_name); 
    }
    closedir(dirp);

    return 0;
}