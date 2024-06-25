#include <iostream>
#include <memory>
#include <string>
#include <vector>

using std::cin, std::cout, std::endl;

class Point  :
    public std::enable_shared_from_this<Point>
{
public:
    Point(int x, int y) : x_(x), y_(y) {}
    int x() const { return x_; }
    int y() const { return y_; }
    std::shared_ptr<Point> get_shared_this() { return shared_from_this(); }

    std::shared_ptr<Point> addPoint(Point &p) {
        x_ += p.x_;
        y_ += p.y_;
        return shared_from_this();
    }

    void print() const {
        cout << "(" << x_ << ", " << y_ << ")" << endl;
    }

private:
    int x_;
    int y_;
};

void test(){
    Point *p = new Point(1, 2);
    std::unique_ptr<Point> p1(p);
    // std::unique_ptr<Point> p2(p); double free
}

void test1(){
    std::shared_ptr<Point> p1(new Point(1, 2));
    std::shared_ptr<Point> p2(new Point(3, 4));
    std::shared_ptr<Point> p3(p1->addPoint(*p2));
    p3->print();
}

auto main() -> int{

    test1();

    return 0;
}