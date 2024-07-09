#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>


using std::cin, std::cout, std::endl;


class Number
{
public:
    Number(size_t data = 0)
        : _data(data)
    {}
    void print() const {
        std::cout << "Value: " << _data << std::endl;
    }
    //判断是不是偶数
    bool isEven() const { return (0 == _data % 2); }
    //判断是不是质数
    bool isPrime() const
    {
        if (1 == _data) {
            return false;
        }
        //质数/素数
        for (size_t idx = 2; idx <= _data / 2; ++idx) {
            if (0 == _data % idx) {
                return false;
            }
        }
        return true;
    }

private:
    size_t _data;
};

void test0()
{
    std::vector<Number> vec;
    for (int i = 0; i < 15; i++) {
        vec.push_back(Number(i));
    }
    // std::for_each(vec.begin(), vec.end(), std::mem_fn(&Number::print));
    using namespace std::placeholders;
    // std::for_each(vec.begin(), vec.end(), std::bind(&Number::print, _1));
    std::function<void(const Number&)> f = std::bind(&Number::print, _1);

    std::for_each(vec.begin(), vec.end(), f);

    // std::for_each(vec.begin(), vec.end(), [](const Number& num){
    //     num.print();
    // });

}

int main(void)
{

    test0();

    return 0;
}