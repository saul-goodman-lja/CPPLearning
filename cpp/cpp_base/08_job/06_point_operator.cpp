#include <iostream>

using std::cin, std::cout;

class Point{
public:
    Point(int x, int y) : _x(x), _y(y) {}

    void print(){
        cout << "(x, y) = " << "(" << _x << ", " << _y << ")" << std::endl;
    }

    friend Point operator+(const Point &lhs, const Point &rhs);

    Point & operator+=(const Point &rhs){
        this->_x += rhs._x;
        this->_y += rhs._y;
        return *this;
    }

    Point & operator++(){
        this->_x++;
        this->_y++;
        return *this;
    }

    Point operator++(int){
        Point temp(*this);
        this->_x++;
        this->_y++;
        return temp;
    }


private:
    int _x;
    int _y;
};

Point operator+(const Point &lhs, const Point &rhs){
    return Point(lhs._x + rhs._x, lhs._y + rhs._y);
}

int main(void){

    Point p1(1,2);
    Point p2(3,4);

    // Point p3 = operator+(p1, p2);
    Point p3 = p1 + p2;
    p3.print();

    p1.operator+=(p2);
    p1.print();

    (p2++).print();
    p2.print();

    (++p2).print();

    return 0;
}