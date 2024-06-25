#include <iostream>
#include <vector>
#include <memory>

using std::cin, std::cout, std::endl;

class Point :
    public std::enable_shared_from_this<Point>
{
public:
    Point(int x = 0, int y = 0) : _x(x), _y(y){}

    ~Point(){
        cout << "~Point()" << endl;
    }

    Point(const Point & rhs){
        _x = rhs._x;
        _y = rhs._y;
        cout << "Point(const Point & rhs)" << endl;
    }

    Point & operator=(const Point & rhs){
        cout << "operator = " << endl;
        if(this != &rhs){
            _x = rhs._x;
            _y = rhs._y;
        }
        return *this;
    }

    void print(){
        cout << "(" << _x << "," << _y << ")" << endl;
    }

    std::shared_ptr<Point> get_shared_ptr(){
        return shared_from_this();
    }

private:
    int _x, _y;
};

void test0(){
    std::auto_ptr<int> abs(new int(10));
    std::auto_ptr<int> abs2(abs);

    //auto_ptr<int> abs2(abs)； 这一步表面上执行了拷贝操作，
    //但是底层已经将右操作数ap所托管的堆空间的控制权交给了左操作数ap2，
    //并且将ap底层的指针数据成员置空，该拷贝操作存在隐患，所以auto_ptr被弃用了。

    cout << *abs << endl;
    cout << *abs2 << endl;
}

void test1(){
    std::unique_ptr<int> up = std::make_unique<int>(10);
    cout << "*up = " << *up << endl;
    cout << "address = " << up.get() << endl;

    // std::unique_ptr<int> up1 = up; 无法复制
    std::unique_ptr<int> up2 = std::make_unique<int>(10);
    // up2 = up; 无法赋值

    std::vector<std::unique_ptr<Point>> vec;
    // vec.push_back(p); 报错， 只能传递右值
    // vec.push_back(std::move(p));
    // vec.push_back(std::make_unique<Point>(111,2222));
    // vec[0]->print();
    // vec[1]->print();

    

    std::unique_ptr<Point> p = std::make_unique<Point>(1,2);
    vec.emplace_back(std::move(p));
    // vec.push_back(std::move(p));  区别不大，都是移动指针控制权 
    vec[0]->print();

    std::unique_ptr<Point> ptr = std::make_unique<Point>(333,4444);
    vec.emplace_back(ptr.release());// 移交所有权
    // ptr = nullptr;
    vec[1]->print();
    // cout << vec.size() << endl;
}

void test2(){
    // std::shared_ptr<int> s1 = std::make_shared<int>(10);
    // std::shared_ptr<int> sp = std::make_shared<int>(42);
    // int *point  = s1.get();
    // s1.reset(sp.get());
    // delete point;
    // cout << sp.use_count() << endl;
    std::vector<std::shared_ptr<Point>> vec;
    
    std::shared_ptr<Point> sp = std::make_shared<Point>(1,2);
    vec.push_back(std::move(sp)); // 移动指针控制权
    cout << sp.use_count() << endl;
    vec.emplace_back(std::make_shared<Point>(555, 666));
    vec.emplace_back(vec[0]->get_shared_ptr());
    // vec[1].reset(sp);
    vec[0]->print();
    vec[1]->print();
    cout << vec[1].use_count() << endl;
}

int main(){
    test2();
    return 0;
}