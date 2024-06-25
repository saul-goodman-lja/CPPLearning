#include <iostream>

using namespace std;

int main() {
    int a = 1;
    int b = 2;
    int* address1 = reinterpret_cast<int*>(&a); // 示例地址1
    int* address2 = reinterpret_cast<int*>(&b); // 示例地址2
    cout << &a << endl;
    cout << &b << endl;
    // 计算两地址相减并输出十六进制结果
    std::cout << static_cast<size_t>(address2 - address1) << std::endl;

    return 0;
}
