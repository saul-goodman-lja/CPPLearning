#include <iostream>
#include <string>
#include <stdexcept> // 引入标准异常库
#include <climits>
using std::cout, std::endl;

class empty_stack_exception : public std::exception {
public:
    const char* what() const throw() {
        return "Stack is empty!";
    }
};

template <typename T = int, int kCapacity = 10>
class Stack{
public:
    Stack()
    : _top(-1)
    , _data(new T[kCapacity]()) {}

    ~Stack() {
        if(_data){
            delete[] _data;
            _data = nullptr;
        }
    }

    bool empty() const;
    bool full() const;
    void push(const T &);
    void pop();
    T top(); 
private:
    int _top;
    T *_data;
};

template <typename T, int kCapacity>
bool Stack<T, kCapacity>::empty() const {
    return _top == -1;
}

template <typename T, int kCapacity>
bool Stack<T, kCapacity>::full() const {
    return _top == kCapacity - 1;
}

template <typename T, int kCapacity>
void Stack<T, kCapacity>::push(const T &t) {
    if(full()){
        std::cout << "stack is full" << std::endl;
        return;
    }
    _data[++_top] = t;
}

template <typename T, int kCapacity>
void Stack<T, kCapacity>::pop() {
    if(empty()){
        std::cout << "stack is empty" << std::endl;
        return;
    }
    _top--;
}

template <typename T, int kCapacity>
T Stack<T, kCapacity>::top() {
    if(empty()){
        // std::cout << "stack is empty" << std::endl;
        // return T();
        throw empty_stack_exception(); // 当栈为空时抛出异常
    }
    return _data[_top];
}

void test0(){
    Stack<std::string, 20> ss;
    Stack<int,5> sta1;
    cout << "is stack empty? " << sta1.empty() << endl;
    sta1.push(1);
    sta1.push(1);
    sta1.push(1);
    sta1.push(1);
    sta1.push(1);
    cout << "is stack full? " << sta1.full() << endl;
    // ss.push("const basic_string<char> &");
    cout << ss.top() << endl;

    Stack<> sta2;
    sta2.push(123654);
    cout << sta2.top() << endl;
}

auto main(void) -> int{
    int a = INT_MAX;
    int && t = std::move(a);
    // t = a;
    a = 3;
    cout << a << endl;
    cout << t << endl;
    // test0();
    return 0;
}