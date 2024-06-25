#include <iostream>

using std::cout, std::endl;

class Base{
public:
    Base(int val) : _val(val) {}
 
    friend int operator+(const Base & lhs, const Base & rhs);  

private:
    int _val;
};

int operator+(const Base & lhs, const Base & rhs){
    return rhs._val - lhs._val;
}   


int main(void){
    int i=2;
    int j=7;

    Base x(i);
    Base y(j);
    cout << (x+y == j - i) << endl;
}