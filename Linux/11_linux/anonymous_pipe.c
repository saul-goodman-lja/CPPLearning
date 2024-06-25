#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PIPE_READ 0
#define PIPE_WRITE 1

int main(int argc, char *argv[])
{

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    { // 检查pipe调用是否成功
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    char buf[4096] = {0};
    int count = 0;

    while (count < 10)
    {                                  // 限制循环次数避免无限循环
        memset(buf, 'A', sizeof(buf)); // 填充buf以便观察到写入操作
        ssize_t bytes_written = write(pipe_fd[PIPE_WRITE], buf, sizeof(buf));
        if (bytes_written == -1)
        {
            perror("write");
            break; // 写入出错时跳出循环
        }

        printf("写入 4096 字节成功，次数 = %d\n", ++count);
        close(pipe_fd[PIPE_READ]);

        // 对于这个例子，不立即关闭读端
    }
    // 循环完成后关闭资源
    close(pipe_fd[PIPE_WRITE]);

    return 0;
}