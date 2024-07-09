#include <my_header.h>
#include <iostream>
int main(int argc, char *argv[]) {

    int n = 10000;
    int i = 0;
    while (n--) {
        std::cout << "test-----------测试次数 = " << i++ << std::endl;
        system("./a.out");
    }
    return 0;
}