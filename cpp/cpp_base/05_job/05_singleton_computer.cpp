#include <iostream>
#include <string.h>
using std::cin, std::cout, std::endl;

class Computer{

public:
    static Computer * getInstance(){
        if(nullptr == _pInstance){
            _pInstance = new Computer("unkonwn", 0);
        }
        return _pInstance;
    }

    void modify(const char *brand, double price){
        if(_brand){
            delete [] _brand;
            _brand = nullptr;
        }
        _brand = new char[strlen(brand) + 1]();
        strcpy(_brand, brand);
        _price = price;
    }

    void print(){
        cout << "brand: " << _brand << ", price: " << _price << endl;
    }

    static void destroy(){
        if(_pInstance){
            delete _pInstance;
        }
    }

private:
    char *_brand;
    double _price;

    static Computer *_pInstance;

    Computer(const char *brand, double price) : 
        _brand(new char[strlen(brand) + 1]()),
        _price(price){
            strcpy(_brand, brand);
        }

    ~Computer(){
        if(_brand){
            delete[] _brand;
        }
        _brand = nullptr;
    }

    Computer(const Computer & rhs) = delete;

    Computer & operator=(const Computer & rhs) = delete;
};

Computer * Computer::_pInstance = nullptr;

int main(void){

    Computer::getInstance()->print();

    Computer::getInstance()->modify("hauwei", 8555);

    Computer::getInstance()->print();

    Computer::getInstance()->destroy();

    return 0;
}