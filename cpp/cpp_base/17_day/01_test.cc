#include <iostream>
#include <vector>
#include <memory>
#include <string>

using std::cin, std::cout, std::endl;

class Point{
public:
    Point(int x = 0, int y = 0) : _x(x), _y(y) {}

    ~Point(){
        cout << "destructed" << endl;
    }
    void print(){
        cout << "(" << _x << ", " << _y << ")" << endl;
    }

private:
    int _x;
    int _y;
};

class MyClass {
public:
    MyClass() { std::cout << "MyClass constructed" << std::endl; }
    ~MyClass() { std::cout << "MyClass destructed" << std::endl; }
};

void test(){
    std::unique_ptr<Point> up1 = std::make_unique<Point>(1, 2);
    std::vector<std::unique_ptr<Point>> vec;
    {
        vec.push_back(std::unique_ptr<Point>(new Point(3, 4)));
        vec[0]->print();
    }
    std::cin.get();
}

void test1(){
    std::shared_ptr<int> a = std::make_shared<int>(5);
    std::weak_ptr<int> b = a;
    cout << b.use_count() << endl;
    std::shared_ptr<int> c= b.lock();
    cout << b.use_count() << endl;
}

void test2(){
    using FileCloserType = void(*)(FILE*);
    FileCloserType FILECloser = [] (FILE *fp){
        if(fp != nullptr){
            fclose(fp);
        }
    };
    std::string msg = "hello";
    // std::unique_ptr<FILE, decltype(FILECloser)> up(fopen("test.txt", "a+"), FILECloser);
    std::unique_ptr<FILE, FileCloserType> up(fopen("test.txt", "a+"), FILECloser);
    fwrite(msg.c_str(), 1, msg.size(), up.get());

}
int main() {
    
    // std::vector<std::shared_ptr<MyClass>> vec;
    // vec.push_back(std::make_shared<MyClass>());
    // std::shared_ptr<MyClass> sp = vec[0];
    // cout << sp.use_count() << endl;

    test2();

    return 0;
}