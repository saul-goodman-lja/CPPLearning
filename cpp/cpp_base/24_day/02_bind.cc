#include <iostream>
#include <functional>


using std::bind;
using std::cin, std::cout ,std::endl;

int add(int a, int b, int c){
    return a + b + c;
}
int main(){
    int x = 1;
    using namespace std::placeholders;
    auto f = bind(add, _1, _1, _1);

    x++;

    cout << f(1) << endl;

    return 0;
}