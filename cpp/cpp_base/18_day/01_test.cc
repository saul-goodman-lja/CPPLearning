#include <iostream>
#include <memory>
#include <cstdio>

int main() {
    // 定义自定义删除器 lambda 表达式来关闭 FILE*
    auto fileCloser = [](FILE* file) {
        if (file) {
            fclose(file);
            std::cout << "File closed." << std::endl;
        }
    };

    // 创建智能指针 std::unique_ptr，传入自定义删除器
    const char* filename = "example.txt";
    FILE* file = fopen(filename, "w");
    if (file == nullptr) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    std::unique_ptr<FILE, decltype(fileCloser)> filePtr(file, fileCloser);
    
    fwrite("Hello, World!", 1, 13, filePtr.get());
    // 在这之后，您可以使用 filePtr 来操作 FILE*，无需手动释放资源
    // 当智能指针 filePtr 超出作用域时，文件资源将自动释放

    return 0;
}