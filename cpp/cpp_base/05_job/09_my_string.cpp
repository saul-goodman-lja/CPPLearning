#include <iostream>
#include <string.h>

using std::cin, std::cout, std::endl;

class String{

public:
    String() : _pstr(nullptr){
        cout << "default" << endl;
    }
    
    // explicit String(const char *pstr) : 
    //     _pstr(new char[strlen(pstr) + 1]()){
    //         strcpy(_pstr, pstr);
    //     cout << "constructor" << endl;
    // }

    String(const char *pstr) : 
        _pstr(new char[strlen(pstr) + 1]()){
            strcpy(_pstr, pstr);
        cout << "constructor" << endl;
    }

    String(const String & rhs) : 
        _pstr(new char[strlen(rhs._pstr) + 1]()){
        strcpy(_pstr, rhs._pstr);
        cout << "copy" << endl;
    }

    ~String(){
        delete [] _pstr;
        cout << "destroy" << endl;
    }

    String & operator=(const String & rhs){
        if(&rhs != this){
            delete [] _pstr;   
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
        }
        cout << "operator" << endl;
        return *this;
    }

    void print(){
        cout << "---" << endl;
        cout << (_pstr ? _pstr : "null") << endl;
    }

    size_t length() const{
        return strlen(_pstr);
    }

    const char *c_str() const{
        return _pstr;
    }

private:
    char *_pstr;
};

int main(void){

    // String str1;
    // str1.print();
    String str2 = "Hello, world";
    // String str2 = String("Hello, world");
    // String str3("wangdao");

    str2.print();
    // str3.print();

    // String str4 = str3;
    // str4.print();

    // str4 = str2;
    // str4.print();

    return 0;
}