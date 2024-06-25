#include <iostream>
#include <string>

using std::cin, std::cout, std::endl;
using std::string;

template <typename T>
T add(T a, T b){
    return a + b;
}

void test0(){
    cout << add(1, 2) << endl;
    cout << add(1.2, 2.3) << endl;
    string a = "hello";
    string b = "world";
    cout << add(a, b) << endl;
}
int main(void){

    test0();

    return 0;
}