#include <iostream>

using std::cout, std::endl;

class Singleton{

    class AutoRelease{
        public:
            AutoRelease() {}
            ~AutoRelease() {
                cout << "!Autorelease" << endl;
                if(_pInstance){
                    delete _pInstance;
                    cout << "delete success" << endl;
                    _pInstance = nullptr;
                }
            }
    };
public:
    static Singleton * getInstance(){
        if(_pInstance == nullptr){
            _pInstance = new Singleton();
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
    static Singleton * _pInstance;
    static AutoRelease _ar;
    Singleton(int x = 0, int y = 0) : _x(x), _y(y) {}
    ~Singleton() {}
    Singleton(const Singleton&) = delete;
    Singleton & operator=(const Singleton&) = delete;
};

Singleton * Singleton::_pInstance = nullptr;
Singleton::AutoRelease Singleton::_ar;

int main(void){

    Singleton::getInstance()->init(111, 222);
    Singleton::getInstance()->print();
    Singleton::getInstance()->destroy();

    return 0;
}