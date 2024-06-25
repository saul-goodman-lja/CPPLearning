#include <iostream>
#include <iomanip>
#define PI 3.1415926

using std::cin, std::cout, std:: endl;

class Circle{
public:
    Circle() : _radius(0) {}
    Circle(double r) : _radius(r) {}

    double getArea(){
        return PI * _radius * _radius;
    }

    double getPerimeter(){
        return 2 * PI * _radius;
    }   

    void show(){
        cout << "Radius = " << std::fixed << std::setprecision(2) << _radius << endl;
        cout << "Perimeter = " << std::fixed << std::setprecision(2) << getPerimeter() << endl;
        cout << "Area = " << std::fixed << std::setprecision(2) << getArea() << endl;
    }

private:
    double _radius;
};

class Cylinder : public Circle{
public:
    Cylinder(double r, double h) :
        Circle(r),
        _hight(h) {}

    double getVolume(){
        return getArea() * _hight;
    }

    void showVolume(){
        cout << "Volume = " << std::fixed << std::setprecision(2) << getArea() << endl;
    }

private:
    double _hight;
};

void test0(){
    Circle c1(1.55);
    c1.show();
}

void test1(){
    Cylinder c1(2.5, 4.5);
    c1.show();
    c1.showVolume();
}

int main(){

    test1();

    return 0;
}