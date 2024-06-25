#include <iostream>

using std::cout;
using std::endl;

class Data{
public:
    Data(int a = 0) : x(a) {}

    Data(const Data & rhs){
        
    }

    void print(){
        cout << "sdaw" << std::endl;
    }

    operator int(){
        return this->x;
    }
private:
    int x;
};


int main(void){

    Data * const data = new Data();

    // Data d = (Data)5;
    Data d(50);
    int a = (int)d;

    

    return 0;
}