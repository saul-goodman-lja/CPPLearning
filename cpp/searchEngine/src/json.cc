#include "../nlohmann/json.hpp"
#include <iostream>
#include <vector>
int main(){

    // 创建一个字符串数组
    std::vector<std::string> stringArray = {"apple", "banana", "cherry"};

    // 将字符串数组封装成 JSON
    nlohmann::json jsonArray = stringArray;

    // 输出 JSON 字符串
    std::cout << jsonArray.dump(4) << std::endl; // 4 是缩进空格数

    return 0;
}