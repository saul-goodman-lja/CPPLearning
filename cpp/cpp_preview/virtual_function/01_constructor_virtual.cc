#include <iostream>

using std::cout, std::endl;

class Grandpa{

public:
    
    Grandpa(){
        cout << *(long long *)this << "---grandpa" <<endl;
    }

    virtual void show(){
        cout << "Grandpa" << "\n";
    }

};

class Parent :
    public Grandpa
{

public:

    Parent(){
        show();
        cout << *(long long *)this << "---parent" << endl;
    }

    ~Parent(){

        show();
    }

};

class Son :
    public Parent
{

public:

    Son(){
        cout << *((long long *)this) << "---son virtual table" << endl;
    }

    ~Son(){}

    virtual void show() override{
        cout << "son" << "\n";
    }

    void test(int x){
        a = x;
    }
private:
    int a;
};

void test0(){
    Son s;
    cout << " --------------" << endl;
    void (Son::*pv)(int) = &Son::test;

    Parent p;
    // Grandpa *p = &s;
    // cout << *(ssize_t *)p << "---" << p << endl;
    // s.~Son();
    // cout << *(long *)p << "---" << p << endl;

}

int main(){
    test0();
    return 0;
}