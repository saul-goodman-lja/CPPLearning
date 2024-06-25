#include <iostream>

using std::cin, std::cout, std::endl;

class Singleton{
public:
    static Singleton * getInstance(){
        pthread_once(&_once, init_r);
        return _pInstance;
    }

    void init(int a, int b){
        _x = a;
        _y = b;
    }

    void print(){
        cout << "(" << _x << ", " << _y << ")" << endl;
    }
private:
    static void init_r(){
        _pInstance = new Singleton(111, 222);
        atexit(destroy);
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
    static pthread_once_t _once;

    Singleton(int a = 0, int b = 0) : _x(a), _y(b) {}
    ~Singleton() {}
    Singleton(const Singleton &) = delete;
    Singleton & operator=(const Singleton &) = delete;
};
Singleton * Singleton::_pInstance = nullptr;
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

int main(void){

    Singleton::getInstance()->print();
    Singleton::getInstance()->init(888, 999);
    Singleton::getInstance()->print();

    return 0;
}