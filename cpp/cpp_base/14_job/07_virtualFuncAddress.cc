#include <iostream>

using std::cout, std::endl;

class Base{
public:
    virtual void show(){
        cout << "---Base show---" << endl;
    }
    virtual void setter(){
        cout << "---Base setter---" << endl;
    }
    virtual long getNum(){
        cout << "Base getInt---" << endl;
        return _base;
    }
private:
    long _base = 20314;
};

class Derived :
    public Base
{
public:
    // virtual void show() override {
    //     cout << "---Derived show---" << endl;
    // }
    virtual void setter() override {
        cout << "---Derived setter---" << endl;
    }
    virtual long getNum() override {
        cout << "---Derived getInt---" << endl;
        return _derived;
    }
private:
    long _derived = 12654;
};

void test(){
    Derived derived;
    long *dp = reinterpret_cast<long *>(&derived);
    cout << dp[0] << endl;
    cout << dp[1] << endl;
    cout << dp[2] << endl;

    cout << ((long *)*dp)[0] << endl;
    cout << ((long *)*dp)[1] << endl;
    cout << ((long *)*dp)[2] << endl;

    void (*func)() = (void(*)())((long *)*dp)[0];
    func();
    func = (void(*)())((long *)*dp)[1];
    func();
    func = (void(*)())((long *)*dp)[2];
    func();

    typedef void(*Func)();
    Func f = (Func)reinterpret_cast<long *>(*dp)[0];
    f();
}

auto main() -> int {
    test();
    return 0;
}