#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>

using std::cin, std::cout, std::endl;

class Point{
public:
    Point(float x = 0, float y = 0)
    : _ix(x)
    , _iy(y){}

    float getX(){
        return _ix;
    }

    float getY(){
        return _iy;
    }

private:
    float _ix;
    float _iy;
};

class Color{
public:
    Color(const char *color = "unknown")
    : _color(new char[strlen(color) + 1]()){
        strcpy(_color, color);
    }

    ~Color(){
        if(_color){
            delete [] _color;
            _color = nullptr;
        }
    }

    void printColor(){
        cout << "Color: " << _color << endl;
    }

private:
    char *_color;
};

class Line{
public:
    Line(const Point &start, const Point &end)
    : _start(start)
    , _end(end){}
    
    Line(float x1 = -1, float y1 = -1, float x2 = -1, float y2 = -1)
    : _start(x1, y1)
    , _end(x2, y2){}

    float getLine(){
        return sqrt((_start.getX() - _end.getX()) * (_start.getX() - _end.getX()) + (_start.getY() - _end.getY()) * (_start.getY() - _end.getY()));
    }

private:
    Point _start;
    Point _end;
};

class Triangle :
    public Line,
    public Color
{
public:
    Triangle(float x1 = -1, float y1 = -1, float x2 = -1, float y2 = -1, 
        const char *color = "unknown", float height = -1)
    : Line(x1, y1, x2, y2)
    , Color(color)
    , _height(height){ }

    float getPerimeter(){
        float _base = getLine();
        return _base + _height + sqrt(_base * _base + _height * _height);
    }

    float getArea(){
        return getLine() * _height / 2;
    }

    void show(){
        printColor();
        cout << "Perimeter: " << std::fixed << std::setprecision(2) << getPerimeter() << endl;
        cout << "Area: " << std::fixed << std::setprecision(2) << getArea() << endl;
    }

private:
    float _height;
};

void test0(){
    Triangle t1(1, 0, 4, 0, "purple", 4);
    t1.show();
}

int main(){

    test0();

    return 0;
}