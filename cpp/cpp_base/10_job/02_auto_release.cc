#include <iostream>

using std::cout, std::endl;

class Singleton{
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
        cout << "x = " << _x << ", " << "y = " << _y << endl;
    }

private:
    int _x;
    int _y;
    static Singleton *_pInstance;
    Singleton(int x = 0, int y = 0) : _x(x), _y(y) {}
    ~Singleton() {}
    Singleton(const Singleton &) = delete;
    Singleton & operator=(const Singleton &) = delete;
    friend class AutoRelease;
};

class AutoRelease{
public:
    AutoRelease(Singleton *p) : _p(p) {}

    ~AutoRelease(){
        if(_p){
            delete _p;
            _p = nullptr;
        }
    } 
private:
    Singleton *_p;
};
Singleton * Singleton::_pInstance = nullptr;

int main(void){

    AutoRelease auto_release(Singleton::getInstance());

    Singleton::getInstance()->init(1, 2);
    Singleton::getInstance()->print();

}