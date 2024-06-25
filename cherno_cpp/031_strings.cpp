#include <iostream>
#include <string>

void PrintString(const std::string& string)
{
    std::cout << string << std::endl;
}

int main()
{
    std::string name = "cherno" + " hello";
     // 两个 " " 直接相加

    std::string name1 = std::string("cherno") + " hello";

    // find 找到后返回下标 ， 找不到返回 npos
    bool contains = name.find("no") != std::string::npos;

    std::cout << name1 << std::endl;
}
