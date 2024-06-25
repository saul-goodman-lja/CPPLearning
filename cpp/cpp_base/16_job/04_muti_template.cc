#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cin, std::cout, std::endl;
using std::string, std::vector;

double add() {
    return 0;
}

template <typename T, typename ...Args>
double add(T x, Args ...args) {
    return x + add(args...);
}

void test(){
    double rst = add(0, 1.1, 2.2, 3, 4, 5, 6, 7, 8, 9, 10);
    cout << rst << endl;
}

auto main(void) -> int{
    test();
    return 0;
}