#include <iostream>
#include <string>

using std::cin, std::string, std::cout;

int main()
{   

    using namespace std::string_literals;

    std::string name0 = "cherno"s + "hello"; // function s

    std::wstring nameL = L"cherno"s + L" hello";

    std::u32string nameU = U"cherno"s + U" hello";

    const char *example = R"(Line1
Line2
Line3
Line4)";
    
    const char* ex = "Line1\n"
        "Line2\n"
        "Line3\n"
        "Line4\n";

    // string literals 不可修改
    const char name[10] = "ch\0erno \0";

    const char *str = "cherno";
    char *p = (char *)"cherno";
    // p[2] = 'a';

    const char *name1 = u8"cherno"; // normal 每个字符一个字节

    const wchar_t *name2 = L"cherno"; // depend on 环境

    const char16_t *name3 = u"cherno";// char 占两个字节
    const char32_t *name4 = U"cherno";// char 占四个字节

    std::cout << example << " " << std::endl;
}