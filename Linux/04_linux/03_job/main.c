#include <my_header.h>

typedef struct {
    char name[31]; // 姓名（30个字符 + 1个终止符）
    int age;       // 年龄
    char gender;   // 性别 ('M' 或 'F')
} Person;

void serialize(const char *filename, Person *p){
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    ERROR_CHECK(fd, -1, "open fd");

    ssize_t bytes_written = write(fd, p, sizeof(Person));
    ERROR_CHECK(bytes_written, -1, "write");
    
    if(bytes_written != sizeof(Person)){
        fprintf(stderr, "Error: not all bytes are written!\n");
        close(fd);
        exit(1);
    }
    close(fd);
}

void deserialize(const char *filename, Person *p){
    int fd = open(filename, O_RDONLY);
    ERROR_CHECK(fd, -1, "open fd");

    ssize_t bytes_read = read(fd, p ,sizeof(Person));
    ERROR_CHECK(bytes_read, -1, "read");
    if(bytes_read != sizeof(Person)){
        close(fd);
        fprintf(stderr, "Error: not all bytes were read.\n");
        exit(1);
    }
    close(fd);
}
int main(int argc, char *argv[]){

    Person p = {"Mick", 22 ,'m'};
    serialize(argv[1], &p);
    Person p2;
    deserialize(argv[1], &p2);
    printf("Name: %s\n", p2.name);
    printf("Age: %d\n", p2.age);
    printf("Gender: %c\n", p2.gender);
    return 0;
}