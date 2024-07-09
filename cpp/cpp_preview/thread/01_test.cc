#include <iostream>
#include <thread>
#include <string>
#include <functional>

using std::cin, std::cout, std::endl;
using std::thread;
using std::string;
using std::function, std::bind;
void func(const string &name){
    cout << "hello world" << endl;
    cout << name << ": " << std::this_thread::get_id() << endl;
}

class Example{
public:
    void operator()(const string &name){
        cout << name << ": " << std::this_thread::get_id() << endl;
    }
};
void test0(){
    void (*P)(const string &n) = func;
    thread t1(P, "hello world");
    cout << "main: " << std::this_thread::get_id() << endl;
    t1.join();
}

void test1(){
    Example e;
    thread t1(e, "hello world");
    cout << "main: " << std::this_thread::get_id() << endl;
    t1.join();
}

void test2(){
    function<void(const string &)> func = [&] (const string &name) -> void {
        cout << name << ": " << std::this_thread::get_id() << endl;
    };
    thread t1(func, "hello world");
    cout << "main: " << std::this_thread::get_id() << endl;
    t1.join();
}
void test3(){
    auto func = [&] (const string &name) -> void {
        cout << name << ": " << std::this_thread::get_id() << endl;
    };
    thread t1(func, "hello world");
    cout << "main: " << std::this_thread::get_id() << endl;
    t1.join();
}
void test4(){
    function<void(const string &)> f = bind(func, std::placeholders::_1);
    thread t1(f, "hello world");
    cout << "main: " << std::this_thread::get_id() << endl;
    t1.join();
}

void test5(){
    using pFunc = void(&)(const string &);
    pFunc f = func;
    thread t1(f, "hello world");
    cout << "main: " << std::this_thread::get_id() << endl;
    t1.join();
}
int main(void){

    test4();

    return 0;
}