#include <iostream>

using std::cin, std::cout, std::endl;

class Singleton{
public:
    static Singleton * getInstance(){
        if(nullptr == _pInstance){
            atexit(destroy);
            _pInstance = new Singleton(111, 222);
        }
        return _pInstance;
    }


    void init(int x, int y){
        _x = x;
        _y = y;
    }

    void print(){
        cout << "(" << _x << ", " << _y << ")" << endl;
    }

    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

private:
    int _x;
    int _y;
    static Singleton *_pInstance;

    Singleton(int a = 0, int b = 0) : _x(a), _y(b) {}
    ~Singleton(){}
    Singleton(const Singleton &) = delete;
    Singleton & operator=(const Singleton &) = delete;
};

Singleton * Singleton::_pInstance = nullptr;

int main(void){

    Singleton::getInstance()->print();
    Singleton::getInstance()->init(555, 666);
    Singleton::getInstance()->print();
    Singleton::getInstance()->destroy();

    return 0;
}
