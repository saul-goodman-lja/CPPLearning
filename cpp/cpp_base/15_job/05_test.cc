#include <iostream>
using std::cout;
using std::endl;
class A
{
public:
    // A(){
    //     cout << "A default" << endl;
    // }
    A(double a)
    : _a(a)
    {
        cout << "A(double)" << endl;
    }

    ~A(){cout << "~A()" << endl;}
private:
    double _a = 10;
};

class B
: virtual public A
{
public:
    B(double a, double b)
    : A(a)
    , _b(b)
    {
        cout << "B(double,double)" << endl;
    }

    ~B(){ cout << "~B()" << endl; }
private:
    double _b;
};


class C
: virtual public A
{
public:
    C(double a, double c)
    : A(a)
    , _c(c)
    {
        cout << "C(double,double)" << endl;
    }

    ~C(){ cout << "~C()" << endl; }
private:
    double _c;
};

class D
: public B
, public C
{
public:
    D(double a,double b,double c,double d)
    : A(a)
    , B(a,b)
    , C(a,c)
    , _d(d)
    {
        cout << "D(double * 4)" << endl;
    }

    ~D(){ cout << "~D()" << endl; }
private:
    double _d;
};

int main(){
    D d(1,2,3,4);
}