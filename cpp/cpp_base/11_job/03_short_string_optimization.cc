#include <iostream>
#include <string.h>

using std::cin, std::cout, std::endl;
using std::size_t, std::ostream;

class String{
public:
    String(const char *);
    ~String();
    char & operator[](size_t);
    friend ostream & operator<<(ostream &, const String &);

private:
    union Buffer{
        char *_pointer = nullptr;
        char _local[16];
    };
    size_t _size;
    size_t _capacity;
    Buffer _buffer;
};

String::String(const char *pstr){
    _size = strlen(pstr);
    _capacity = _size + 1;
    if(_size < 16){
        memset(_buffer._local, 0, 16);
        strcpy(_buffer._local, pstr);
    }else{
        _buffer._pointer = new char[_capacity]();
        strcpy(_buffer._pointer, pstr);
    }
}
String::~String(){
    if(_size >= 16 && _buffer._pointer){
        delete [] _buffer._pointer;
        _buffer._pointer = nullptr;
    }
}

char & String::operator[](size_t idx){
    if(idx >= 0 && idx < _size){
        if(_size < 16){
            return _buffer._local[idx];
        }else{
            return _buffer._pointer[idx];
        }
    }else{
        cout << "out of range" << endl;
        static char nullchar = '\0';
        return nullchar;
    }
}
ostream & operator<<(ostream &os, const String &rhs){
    if(rhs._size < 16){
        os << rhs._buffer._local;
    }else{
        os << rhs._buffer._pointer;
    }
    return os;
}

void test0(){
    String str1("hello");
    String str2("hello,world!!!!!");
    cout << str1 << endl;
    cout << str2 << endl;
}
int main(void){
    test0();
    return 0;
}