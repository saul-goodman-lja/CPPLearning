#include <my_header.h>

int main(int argc, char *argv[]){

    ARGS_CHECK(argc, 1);

    int pipe_read = open("1.pipe", O_RDONLY);
    ERROR_CHECK(pipe_read, -1, "open 1.pipe");

    int len_name;
    read(pipe_read, &len_name, sizeof(int));
    char name[20] = {0};
    read(pipe_read, name, len_name);

    int len_file;
    read(pipe_read, &len_file, sizeof(int));

    int len_contents;
    read(pipe_read, &len_contents, sizeof(len_contents));
    char contents[1024] = {0};
    read(pipe_read, contents, len_contents);

    contents[len_contents] = '\n';
    contents[len_contents+1] = '\0';

    mkdir("files", 0777);
    chdir("files");

    int file_fd = open(name, O_RDWR | O_CREAT, 0666);
    ftruncate(file_fd, len_file);
    write(file_fd, contents, len_contents + 1);


    close(pipe_read);
    close(file_fd);

    return 0;
}