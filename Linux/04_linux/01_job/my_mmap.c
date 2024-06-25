#include <my_header.h>

#define COPY_SIZE (1024 * 1024 * 8)

long long current_time_millis()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);                          // 获取当前时间
    return (long long)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000; // 转换为毫秒
}
int main(int argc, char *argv[])
{

    long start = current_time_millis();

    ARGS_CHECK(argc, 3);

    int src_fd = open(argv[1], O_RDONLY);
    ERROR_CHECK(src_fd, -1, "open ssrc");

    long src_size = lseek(src_fd, 0, SEEK_END);

    int dest_fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
    ERROR_CHECK(dest_fd, -1, "open dest_fd");

    int ret2 = ftruncate(dest_fd, src_size);
    ERROR_CHECK(ret2, -1, "ftruncate");

    // copied bytes
    off_t offset = 0;
    while (offset < src_size)
    {
        off_t cur_size = (offset + COPY_SIZE < src_size) ? COPY_SIZE : src_size - offset;

        void *srcp = mmap(NULL, cur_size, PROT_READ, MAP_SHARED, src_fd, offset);
        ERROR_CHECK(srcp, NULL, "mmap srcp");

        void *destp = mmap(NULL, cur_size, PROT_READ | PROT_WRITE, MAP_SHARED, dest_fd, offset);
        ERROR_CHECK(destp, NULL, "mmap destp");

        memcpy(destp, srcp, cur_size);

        munmap(srcp, cur_size);
        munmap(destp, cur_size);

        offset += cur_size;
    }

    char ch;
    for (int i = 0; i < src_size; i++)
    {
        ssize_t sret = read(dest_fd, &ch, 1);
        if (sret == 0)
        {
            break;
        }
        ch = tolower(ch);
        lseek(dest_fd, -1, SEEK_CUR);
        write(dest_fd, &ch, 1);
    }

    close(src_fd);
    close(dest_fd);

    long end = current_time_millis();
    printf("time = %ld\n", (end - start));
    return 0;
}