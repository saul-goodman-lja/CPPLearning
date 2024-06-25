#include <iostream>

using std::cin, std::cout, std::endl;

template <typename T>
class RAII{
public:
    RAII(T *data) : _data(data) {}

    ~RAII() {
        if(_data){
            delete _data;
            _data = nullptr;
        }
    }

    T * operator->() {
        return _data;
    }

    T & operator*() {
        return *_data;
    }

    T *get () const {
        return _data;
    }

    void set(T *data){
        if(_data){
            delete _data;
            _data = nullptr;
        }
        _data = data;
    }

    RAII(const RAII &) = delete;
    RAII & operator=(const RAII &) = delete;

private:
    T *_data;
};

class Point{
public:
    Point(int x = 0, int y = 0) : _x(x), _y(y) {}

    ~Point() {}


    friend std::ostream & operator<<(std::ostream &, const Point &);

private:
    int _x, _y;
};

std::ostream & operator<<(std::ostream &os, const Point &p){
    os << "(" << p._x << ", " << p._y << ")";
    return os;
}

void test(){
    RAII<int> r1(new int(10));
    cout << *r1 << endl;

    r1.set(new int(22));
    cout << *r1 << endl;
    RAII<Point> r2(new Point(10, 20));
    cout << *r2 << endl;
}

int main(){
    test();
    return 0;
}