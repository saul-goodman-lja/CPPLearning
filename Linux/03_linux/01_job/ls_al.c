#include <my_header.h>

char trans_mode(mode_t mode){
    char c;
    switch (mode & __S_IFMT)
    {
    case __S_IFBLK :
        c = 'b';
        break;
    case __S_IFCHR :
        c = 'c';
        break;
    case __S_IFDIR :
        c = 'd';
        break;
    case __S_IFIFO :
        c = 'p';
        break;
    case __S_IFLNK :
        c = 'l';
        break;
    case __S_IFREG :
        c = '-';
        break;
    case __S_IFSOCK :
        c = 's';
        break;
    default:
        c = 'u';
        break;
    }

    return c;
}

void mode_to_string(mode_t mode, char *str){

    str[0] = trans_mode(mode);

    str[1] = (mode & 0400) ? 'r' : '-';
    str[2] = (mode & 0200) ? 'w' : '-';
    str[3] = (mode & 0100) ? 'x' : '-';

    str[4] = (mode & 0400) ? 'r' : '-';
    str[5] = (mode & 0200) ? 'w' : '-';
    str[6] = (mode & 0100) ? 'x' : '-';

    str[7] = (mode & 0400) ? 'r' : '-';
    str[8] = (mode & 0200) ? 'w' : '-';
    str[9] = (mode & 0100) ? 'x' : '-';
    
    str[10] = '\0';
}

void get_time_str(time_t mtime, char *str){
    char mon_arr[][10] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        'Jul', "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    struct tm *tm_val = localtime(&mtime);
    sprintf(str, "%s %02d %02d:%02d", mon_arr[tm_val->tm_mon],
        tm_val->tm_mday,
        tm_val->tm_hour,
        tm_val->tm_min);
}


int main(int argc, char *argv[]){

    char *dir_name;
    if(argc < 2){
        dir_name = ".";
    }
    else{
        dir_name = argv[1];
    }

    DIR *dirp = opendir(dir_name);
    ERROR_CHECK(dirp,NULL,"opendir");
    
    if(argc == 2){
        int ret = chdir(argv[1]);
        ERROR_CHECK(ret, -1, "chdir");
    }

    struct dirent *pdirent;

    while((pdirent = readdir(dirp)) != NULL){

        struct stat statbuf;
        int ret = stat(pdirent->d_name, &statbuf);
        ERROR_CHECK(ret, -1, "stat");

        char str[1024] = { 0 };
        str[0] = trans_mode(statbuf.st_mode);
        mode_to_string(statbuf.st_mode, str);

        char time_str[1024] = { 0 };
        get_time_str(statbuf.st_mtime, time_str);

        // 文件类型权限 硬链接数 拥有者名 拥有者组名 文件大小 时间 文件名
        printf("%s\t%lu\t%s\t%s\t%4lu\t%s\t%s\n", str,
               statbuf.st_nlink,
               getpwuid(statbuf.st_uid)->pw_name,
               getgrgid(statbuf.st_gid)->gr_name,
               statbuf.st_size,
               time_str,
               pdirent->d_name);
    }

    closedir(dirp);

    return 0;
}