#include <iostream>

using std::cout, std::endl;

class A
{ 
public:
    virtual
    void func(int val = 1)
    {
        cout << "A->" << val << endl;
    }
    virtual void test()
    {
        func();
    }
private:
    long _a;
};

class B
: public A
{ 
public:
    virtual
    void func(int val = 10)
    {
        cout << "B->" << val << endl;
    }
private:
    long _b;
};

class C
: public B
{
    virtual
    void func(int val = 10)
    {
        cout << "C->" << val << endl;
    }   
    
};

int main(void)
{
    B b;
    A *p1 = (A*)&b;
    B *p2 = &b;
    p1->func();
    p2->func();
   
    return 0;
}