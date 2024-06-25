#include <iostream>
using std::cout;
class Point{
public:
    static Point & getInstance(){
        static Point point(1,2);
        return point;
    }

    void print() const{
        cout << "x = " << this->_x << ", ";
        cout << "y = " << this->_y << "\n";
    }
private:
    int _x;
    int _y;

    Point(int x, int y) : _x(x), _y(y) {}
};

void test(){
    Point & p1 = Point::getInstance();
    p1.print();
    Point & p2 = Point::getInstance();
    p2.print();
}

int main(void){
    test();
    return 0;
}