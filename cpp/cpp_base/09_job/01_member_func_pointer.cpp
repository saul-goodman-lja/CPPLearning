#include <iostream>

using std::cout;
using std::endl;

class Data{
public:
    Data(int a = 0) : x(a) {}

    Data(const Data & rhs){
        
    }

    void print(int n){
        cout << "this is print " << n << std::endl;
    }

private:
    int x;
};

void show(){
    cout << "the show" << endl;
}
typedef void (*FuncPointer)();
typedef void(Data::*memberFuncPointer)(int);

int main(void){

    void (*s)() = show;
    s();
    FuncPointer sh = &show;
    sh();

    Data data;
    void (Data::*p)(int) = &Data::print;
    (data.*p)(5);
    memberFuncPointer ptr = &Data::print;
    (data.*ptr)(6);

    Data *data1;
    (data1->*p)(7);
    (data1->*ptr)(8);

    delete data1;
    return 0;
}