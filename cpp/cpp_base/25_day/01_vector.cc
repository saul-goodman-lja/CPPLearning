#include <iostream>
#include <memory>
using std::cin, std::cout, std::endl;

template <typename T>
class Vector{
public:
    Vector();
    ~Vector();
    void push_back(const T &);
    void pop_back();
    int size();
    int capacity();
private:
    void reallocate();
private:
    static std::allocator<T> _alloc;
    T *_start;
    T *_finish;
    T *_end_of_storage;
};
template <typename T>
std::allocator<T> Vector<T>::_alloc = std::allocator<T>();

template <typename T>
Vector<T>::Vector(){
    _start = _alloc.allocate(1);
    _finish = _start;
    _end_of_storage = _start + 1;
}

template <typename T>
Vector<T>::~Vector(){
    for(int i = 0; i < size(); i++){
        std::allocator_traits<std::allocator<T>>::destroy(_alloc, _start + i);
        // _alloc.destroy(_start + i);
    }
    _alloc.deallocate(_start, capacity());
}

template <typename T>
void Vector<T>::reallocate(){
    int oldCapacity = capacity();
    int oldSize = size();
    T *new_start = _alloc.allocate(2 * oldCapacity);
    std::uninitialized_copy(_start, _start + oldSize, new_start);
    for(int i = 0; i < size(); i++){
        // std::allocator_traits<std::allocator<T>>::construct(_alloc, new_start + i, _start[i]);
        std::allocator_traits<std::allocator<T>>::destroy(_alloc, _start + i);
    }
    _alloc.deallocate(_start, oldCapacity);
    _start = new_start;
    _finish = _start + oldSize;
    _end_of_storage = _start + 2 * oldCapacity;
}

template <typename T>
void Vector<T>::push_back(const T & elem){
    if(size() == capacity()){
        reallocate();
    }
    std::allocator_traits<std::allocator<T>>::construct(_alloc,_finish++, elem);
    cout << "push_back " << elem << endl;
    cout << "size: " << size() << endl;
    cout << "capacity: " << capacity() << endl;
}

template <typename T>
void Vector<T>::pop_back(){
    if(size()){
        std::allocator_traits<std::allocator<T>>::destroy(_alloc, --_finish);
        cout << "pop_back" << endl;
        cout << "size: " << size() << endl;
    }else{
        std::cerr << "vector is empty" << endl;
    }
}

template <typename T>
int Vector<T>::size(){
    return _finish - _start;
}
template <typename T>
int Vector<T>::capacity(){
    return _end_of_storage - _start;
}

class Point{
public:
    Point(int x, int y): _x(x), _y(y){}
    ~Point(){
        cout << "~Point" << endl;
    }

    friend std::ostream & operator<<(std::ostream &, const Point &);

private:
    int _x;
    int _y;
};
void test(){
    Vector<Point> v;
    for(int i = 0; i < 10; i++){
        v.push_back(Point(i, i));
    }
    for(int i = 0; i < 10; i++){
        v.pop_back();
    }

}
std::ostream & operator<<(std::ostream & os, const Point & rhs){
    os << "(" << rhs._x << ", " << rhs._y << ")";
    return os;
}

int main(){
    test();
    return 0;
}