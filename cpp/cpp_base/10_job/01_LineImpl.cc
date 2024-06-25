#include "01_Line.hpp"
#include <iostream>

class Line::LineImpl{
public:
    class Point{
    public:
        Point(int x, int y) : _x(x), _y(y) {}
        ~Point() {}
        void print(){
            std::cout << "(" << _x << " ," << _y << ")" << std::endl;
        }
    private:
        int _x;
        int _y;
    };

public:
    LineImpl(int x1, int y1, int x2, int y2) : _p1(x1, y1), _p2(x2, y2) { }
    ~LineImpl(){}
    void printLine(){
        _p1.print();
        _p2.print();
    }

private:
    Point _p1;
    Point _p2;
};

Line::Line(int x1, int y1, int x2, int y2) : _pimpl(new LineImpl(x1, y1, x2, y2)) {}

Line::~Line(){
    if(_pimpl){
        delete _pimpl;
        _pimpl = nullptr;
    }
}
void Line::printLine() const{
    _pimpl->printLine();
}
