#include <my_header.h>

// int main() {

//     char buf[1024] = {0};
//     FILE *pipe = popen("sha1sum 1.txt", "r");
//     //FILE *pipe = popen("md5sum file.txt", "r");
//     fread(buf,1, sizeof(buf), pipe);


//     int len = strlen(buf);
//     char *name = "  1.txt";
//     memset(buf + len - strlen(name), 0, strlen(name));

//     printf("hash: \n%s\n", buf);
//     pclose(pipe);

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define NUM_COLORS 3

// 定义枚举类型
enum Color {
    RED,
    GREEN,
    BLUE
};

// 定义哈希表结构
typedef struct {
    const char *key;
    enum Color value;
} HashEntry;

// 哈希表存储映射关系
HashEntry color_map[NUM_COLORS] = {
    {"RED", RED},
    {"GREEN", GREEN},
    {"BLUE", BLUE}
};

// 哈希函数，这里简单使用字符串的长度
uint32_t hash_function(const char *str) {
    return strlen(str);
}

// 字符串到枚举类型的快速转换函数
enum Color string_to_enum(const char *str) {
    uint32_t index = hash_function(str) % NUM_COLORS;

    if (strcmp(str, color_map[index].key) == 0) {
        return color_map[index].value;
    }

    // 处理查找不到的情况
    return -1; // 或者使用其他方法表示未知值
}

int main() {
    const char *color_str = "GREEN";
    enum Color color = string_to_enum(color_str);

    printf("%d \n", color);

    switch (color) {
        case RED:
            printf("Color is RED\n");
            break;
        case GREEN:
            printf("Color is GREEN\n");
            break;
        case BLUE:
            printf("Color is BLUE\n");
            break;
        default:
            printf("Unknown color\n");
            break;
    }

    return 0;
}