#include <my_header.h>

int main(int argc, char *argv[]){

    ARGS_CHECK(argc,2);
    DIR * dirp = opendir(argv[1]);
    // 检查打开目录流是否成功
    ERROR_CHECK(dirp,NULL,"opendir");
    struct dirent * pdirent;
    // 用于记录目录流指针的位置
    long loc;
    while((pdirent = readdir(dirp)) != NULL){
        printf("inode num = %lu, reclen = %hu, type = %u, name = %s\n\n",
               pdirent->d_ino, pdirent->d_reclen,
               pdirent->d_type,pdirent->d_name);
        if(strcmp("dir1",pdirent->d_name) == 0){
            // 如果当前的目录项表示文件的名字是file1,那么记录文件指针的位置
            loc = telldir(dirp);
        }
    }
    printf("--------------------------\n");     // 一个代码分隔线

    seekdir(dirp,loc);      // 目录流指针回到记录位置
    // 获取目录流指针指向的目录项结构体, 并打印信息
    pdirent = readdir(dirp);        
    printf("inode num = %lu, reclen = %hu, type = %u, name = %s\n\n",
           pdirent->d_ino, pdirent->d_reclen,
           pdirent->d_type,pdirent->d_name);
    // 不要忘记关闭流
    closedir(dirp);
    return 0;

}