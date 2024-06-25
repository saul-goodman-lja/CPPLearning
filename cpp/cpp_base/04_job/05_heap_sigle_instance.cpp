#include <iostream>
using std::cout;
class Point{
public:
    static Point * getInstance(){
        if(nullptr == pInstance){
            pInstance = new Point(1, 2);
        }
        return pInstance;
    }

    void print() const{
        cout << "x = " << this->_x << ", ";
        cout << "y = " << this->_y << "\n";
    }

    void modify(int x, int y){
        _x = x;
        _y = y;
    }

    static void destroy(){
        if(pInstance){
            delete pInstance;
        }
    }

private:
    int _x;
    int _y;

    static Point * pInstance;

    Point(int x, int y) : _x(x), _y(y) {}

    ~Point() {}

    Point(const Point & rhs) = delete;
    Point & operator=(const Point & rhs) = delete;
};

Point * Point::pInstance = nullptr;

void test(){
    Point::getInstance()->print();
    Point::getInstance()->modify(10, 99);
    Point::getInstance()->print();
    Point::destroy();
}

int main(void){
    test();
    return 0;
}