#include <iostream>

class Singleton{

private:
    int _x;
    int _y;
    static Singleton *_pInstance;
    static pthread_once_t _once;
};
Singleton *Singleton::_pInstance = nullptr;
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

int main(void){

    return 0;
}