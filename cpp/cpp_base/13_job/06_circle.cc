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

void test0(){
    Circle c1(1.55);
    c1.show();
}

int main(){

    test0();

    return 0;
}