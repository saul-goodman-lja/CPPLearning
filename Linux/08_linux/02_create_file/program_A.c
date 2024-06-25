#include <my_header.h>

int main(int argc, char *argv[]){

    ARGS_CHECK(argc, 1);

    int pipe_write = open("1.pipe", O_WRONLY);
    ERROR_CHECK(pipe_write, -1, "open 1.pipe");

    char name[20] = {0};
    int length;
    char contents[1024] = {0};
    printf("  请输入文件名: ");
    gets(name);
    printf("请输入文件长度: ");
    scanf("%d",&length);
    printf("请输入文件内容: ");
    getchar();
    gets(contents);

    int len_name = strlen(name);
    write(pipe_write, &len_name, sizeof(int));
    write(pipe_write, name, len_name);

    write(pipe_write, &length, sizeof(int));

    int len_contents = strlen(contents);
    write(pipe_write, &len_contents, sizeof(int));
    write(pipe_write, contents, len_contents);

    close(pipe_write);

    return 0;
}