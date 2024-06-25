#include <iostream>
#include <memory>

using std::cout, std::endl;

class A;
class B;

class A{
public:
    std::weak_ptr<B> ptr;
    A(){
        cout << "A" << endl;
    }

    ~A(){
        cout << "~A" << endl;
    }
};

class B{
public:
    std::shared_ptr<A> ptr;
    B(){
        cout << "B" << endl;
    }
    ~B(){
        cout << "~B" << endl;
    }
};

void test(){
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->ptr = b;
    b->ptr = a;
    cout << a.use_count() << endl;
    cout << b.use_count() << endl;
}
int main(){
    test();
    return 0;
}