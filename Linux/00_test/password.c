#include <my_header.h>

// int main(void){
//         char *password;

//     password = getpass("Enter your password: ");

//     if (password == NULL) {
//         // 处理无法获取密码的情况
//         fprintf(stderr, "Error reading password.\n");
//         exit(EXIT_FAILURE);
//     }

//     printf("Password entered: |%s|\n", password);

//     char *pwd = (char *)password;
//     printf("len = %ld\n", strlen(pwd));
//     // 清除密码缓存，以提高安全性
//     // for (char *p = password; *p != '\0'; ++p) {
//     //     *p = '\0';
//     // }

//     memset(password, 0, strlen(password));

//     printf("password = |%s|\n", password);

//     return 0;
// }

// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>

// int checkPassword(const char *password) {
//     int has_upper = 0;
//     int has_lower = 0;
//     int has_digit = 0;
//     int has_dot = 0;
//     int length = strlen(password);

//     if (length < 8) {
//         return 0;  // 密码长度不足
//     }

//     for (int i = 0; i < length; i++) {
//         if(isupper(password[i])) {
//             has_upper = 1;
//         } else if(islower(password[i])) {
//             has_lower = 1;
//         } else if(isdigit(password[i])) {
//             has_digit = 1;
//         } else if(password[i] == '.') {
//             has_dot = 1;
//         }
//     }

//     // 检查密码是否符合要求
//     if (has_upper && has_lower && has_digit && has_dot) {
//         return 1;  // 密码符合要求
//     } else {
//         return 0;  // 密码不符合要求
//     }
// }

// int main() {
//     char password[50];
//     printf("Enter your password: ");
//     fgets(password, sizeof(password), stdin);

//     // 用strlen将换行符替换为'\0'
//     if (strlen(password) > 0 && password[strlen(password) - 1] == '\n') {
//         password[strlen(password) - 1] = '\0';
//     }

//     if (checkPassword(password)) {
//         printf("Password meets the requirements.\n");
//     } else {
//         printf("Password does not meet the requirements.\n");
//     }

//     return 0;
// }

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 函数用于校验密码是否符合要求
bool validate_password(const char *password) {
    bool has_uppercase = false;
    bool has_lowercase = false;
    bool has_digit = false;
    bool has_special = false;
    const char *special_chars = "()[]{}<>\"'`,;:/\\+-?!=:~|_^%$#@&.";

    if(strlen(password) < 8){
        return false;
    }

    for (size_t i = 0; i < strlen(password); i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            has_uppercase = true;
        } else if (password[i] >= 'a' && password[i] <= 'z') {
            has_lowercase = true;
        } else if (password[i] >= '0' && password[i] <= '9') {
            has_digit = true;
        } else if (strchr(special_chars, password[i]) != NULL) {
            has_special = true;
        }
    }

    // 校验是否包含所需的四种字符类别
    return has_uppercase && has_lowercase && has_digit && has_special;
}

int main() {
    char *pass;
    pass = getpass("pass:");
    // if (validate_password(password)) {
    //     printf("密码符合要求\n");
    // } else {
    //     printf("密码不符合要求\n");
    // }
    for (char *p = pass; *p != '\0'; ++p) {
        *p = '\0';
    }

    return 0;
}