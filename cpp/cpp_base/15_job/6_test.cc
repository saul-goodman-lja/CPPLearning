#include <iostream>
using namespace std;
    class Base
{
public:
    Base(int value)
    {
        // Base 类的构造函数
    }

protected:
    void f(){};
};

class Derived : public Base
{
private:
    int  memberVar;
    Base _base;

public:
    Derived(int value)
        : Base(value)
        , memberVar(value)
        , _base(value)
    {
        // 构造函数体内直接初始化 _base
        f();
    }
};

class Test{
    protected:
        void print(){
            cout << "Test" << endl;
        }
};

int main()
{
    Derived d(1);
    Test t;
    t.print();
    return 0;
}
