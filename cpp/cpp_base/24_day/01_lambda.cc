#include <functional>
#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string, std::function;
using std::cin, std::cout, std::endl;

class Empty{
public:
    Empty() : x(new int()){
        cout << this << endl;
    }
    ~Empty(){
        delete x;
    }
private:
    int *x;
};
void test0()
{
    int  sum = 0;
    auto f   = [&](auto&& func, int i) -> int {
        if (i == 0) {
            return 0;
        }
        return i + func(func, i - 1);
    };
    sum = f(f, 10);
    cout << sum << endl;
}

vector<function<void(const string&)>> vec;
void                                  test()
{
    int    num = 100;
    string name("wangdao");
    vec.push_back([&num, &name](const string& value) {
        cout << "num = " << num << endl;
        cout << "name = " << name << endl;
        cout << "value = " << value << endl;
    });
}
void test2()
{
    for (auto func : vec) {
        func("wuhan");
    }
}
int main(void)
{

    test2();

    return 0;
}