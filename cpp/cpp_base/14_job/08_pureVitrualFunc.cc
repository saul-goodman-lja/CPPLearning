#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using std::cin, std::cout, std::endl;
using std::string;

class Figure{
public:
    virtual string getName() const = 0;
    virtual double getArea() const = 0; 
};

void display(Figure & fig){
    cout << fig.getName() << "的面积是: " << std::fixed << std::setprecision(2) << fig.getArea() << endl;
}

class Rectangle :
    public Figure
{
public:
    Rectangle(double w, double h) 
    : _width(w) 
    , _height(h) {} 
    
    virtual string getName() const override{
        return "Rectangle";
    }

    virtual double getArea() const override{
        return _width * _height;
    }

private:
    double _width;
    double _height;
};

class Circle : 
    public Figure
{
public:
    Circle(double r)
    : _radius(r) {}

    virtual string getName() const override{
        return "Circle";
    }

    virtual double getArea() const override{
        return _radius * _radius * PI;
    }

private:
    double _radius;
    static constexpr double PI = 3.1415926;
};


class Triangle : 
    public Figure
{
public:
    Triangle(double a, double b, double c)
    : _a(a)
    , _b(b)
    , _c(c) {}

    virtual string getName() const override{
        return "Triangle";
    }

    virtual double getArea() const override{
        double p = (_a + _b + _c) / 2;
        return sqrt(p * (p - _a) * (p - _b) * (p - _c));
    }

private:
    double _a;
    double _b;
    double _c;
};

void test(){
    Rectangle r(10, 20);
    Circle c(15);
    Triangle t(3, 4, 5);
    display(r);
    display(c);
    display(t);
}

int main(){
    test();
    return 0;
}