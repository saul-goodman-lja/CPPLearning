#include <iostream>

using std::cin, std::cout, std::endl;

class A{
public:
    virtual void a(){ cout << "A::a()" << endl; } 
    void b() { cout << "A::b()" << endl; }
    virtual void c(){ cout << "A::c()" << endl; } 
    void e() { cout << "A::e()" << endl; }
};

class B{
public:
    virtual void a(){ cout << "B::a()" << endl; } 
    void c(){ cout << "B::c()" << endl; } 
    void d(){ cout << "B::d()" << endl; }
    virtual void f(){ cout << "B::f()" << endl; } 
};

class C
: public A
, public B
{
public:
    virtual void a(){ cout << "C::a()" << endl; } 
    virtual void b(){ cout << "C::b()" << endl; } 
    void c(){ cout << "C::c()" << endl; } 
    void d(){ cout << "C::d()" << endl; } 
};


//先不看D类
class D
: public C
{
public:
    void c(){ cout << "D::c()" << endl; }
};


void test(){
    C c;
    c.a(); //C::a() oversee
    c.b(); //C::b() oversee
    c.c(); //C::c() oversee
    c.d(); //C::d() oversee
    c.e(); //A::e() 访问A的e
    c.f(); //B::f() 访问B的f
    
    cout << endl;
    A* pa = &c;
    pa->a(); //C::a() override 动态多态 访问C的a
    pa->b(); //A::b() 普通访问A的b
    pa->c(); //C::c() override 动态多态 访问C的c
    // pa->Bd(); // 访问失败
    pa->e(); //A::e() 普通访问A的e
    // pa->f(); // 访问失败
    
    cout << endl;
    B* pb = &c;
    pb->a(); //C::a() 通过虚表，goto访问C的a
    // pb->b(); // 访问失败
    pb->c(); //B::c() 普通访问B的c
    pb->d(); //B::d() 普通访问B的d
    // pb->e(); // 访问失败
    pb->f(); //B::f() 通过虚函数指针访问B的f

    cout << endl;
    C * pc = &c;
    pc->a(); //C::a() 是虚函数，没有触发动态多态, 通过虚函数指针访问C的a
    pc->b(); //C::b() 是虚函数，没有触发动态多态, 通过虚函数指针访问C的b
    pc->c(); //C::c() 是虚函数，没有触发动态多态, 通过虚函数指针访问C的c
    pc->d(); //C::d() oversee
    pc->e(); //A::e() 普通访问A的e
    pc->f(); //B::f() 是虚函数，没有触发动态多态, 通过虚函数指针访问B的f
}

int main(){
    test();
    return 0;
}