#include <my_header.h>

int main(int argc, char *argv[]){

    ARGS_CHECK(argc, 2);
    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp, NULL, "opendir");

    int ret = chdir(argv[1]);
    ERROR_CHECK(ret, -1, "chdir");

    struct dirent *pdrient;

    while((pdrient = readdir(dirp)) != NULL){
        struct stat statbuf;
        int ret = stat(pdrient->d_name, &statbuf);
        ERROR_CHECK(ret, -1, "stat");

                // 输出文件相关的信息
        printf("%o\t%lu\t%u\t%u\t%lu\t%lu\t%s\n", 
               statbuf.st_mode,     // 以八进制无符号输出，可以看到权限的数字表示法
               statbuf.st_nlink,    // 无符号长整型输出          
               statbuf.st_uid,      // 无符号int输出
               statbuf.st_gid,      // 无符号int输出
               statbuf.st_size,     // 无符号长整型输出   
               statbuf.st_mtim.tv_sec,     // 时间戳打印秒数，以无符号长整型打印
               pdrient->d_name);        // 字符串打印
    }

    // 关闭目录流
    closedir(dirp);
    return 0;

}
