#include <iostream>

class Line{


    class Point{
    public:
        Point(int x, int y) : _x(x), _y(y) {}

        friend std::ostream & operator<<(std::ostream &, const Point &);
    private:
        int _x;
        int _y;
    };
public:
    Line(int x1, int y1, int x2, int y2) : _p1(x1, y1), _p2(x2, y2) {}
    friend std::ostream & operator<<(std::ostream &, const Point &);
    friend std::ostream & operator<<(std::ostream &, const Line &);
private:
    Point _p1;
    Point _p2;

};

std::ostream & operator<<(std::ostream &os, const Line::Point &rhs){
    os << rhs._x << rhs._y;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Line &rhs){
    os << rhs._p1 << rhs._p2;
    return os;
}

int main(void){

    // Line::Point point(12, 14);
    Line l(1,2,3,4);


    std::cout << l << std::endl;

    return 0;
}