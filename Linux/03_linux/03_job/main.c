#include <my_header.h>
typedef struct
{
    char name[31]; // 姓名，包含一个结束字符
    int age;       // 年龄
    char gender;   // 性别（'M' = 男，'F' = 女）
} Person;
void serialize(Person person, char *args)
{
    int fd = open(args, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    ERROR_CHECK(fd, -1, "open");

    char buffer[1024];
    int len = sprintf(buffer, "Name : %s , Age : %d , Gender : %c\n",
                      person.name,
                      person.age,
                      person.gender);

    if (write(fd, buffer, len) == -1)
    {
        perror("write");
        close(fd);
        exit(1);
    }
    close(fd);
}
Person deserialize(char *args){
    int fd = open(args, O_RDONLY);
    ERROR_CHECK(fd, -1, "open");

    char buffer[1024];
    ssize_t bytes_read = read(fd, buffer,sizeof(buffer) - 1);
    buffer[bytes_read] = '\0';

    Person person;

    int ret = sscanf(buffer, "Name : %s , Age : %d , Gender : %c\n", 
    person.name, 
    &person.age, 
    &person.gender);
    
    if(ret != 3){
        close(fd);
        perror("sscanf");
        exit(1);
    }

    close(fd);

    return person;
}
int main(int argc, char *argv[])
{
    Person person = {"ALice", 20, 'm'};

    serialize(person, argv[1]);

    Person person1 = deserialize(argv[1]);

    return 0;
}