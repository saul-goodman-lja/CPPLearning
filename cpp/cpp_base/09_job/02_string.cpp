#include <iostream>
#include <string.h>
#include <vector>
class String
{

public:
    String();
    String(const char*);
    String(const String&);
    ~String();
    String& operator=(const String&);
    String& operator=(const char*);

    String& operator+=(const String&);
    String& operator+=(const char*);

    char&       operator[](std::size_t index);
    const char& operator[](std::size_t index) const;

    std::size_t size() const;
    const char* c_str() const;

    friend bool operator==(const String&, const String&);
    friend bool operator!=(const String&, const String&);

    friend bool operator<(const String&, const String&);
    friend bool operator>(const String&, const String&);
    friend bool operator<=(const String&, const String&);
    friend bool operator>=(const String&, const String&);

    friend std::ostream& operator<<(std::ostream&, const String&);
    friend std::istream& operator>>(std::istream&, String&);

    void print();

private:
    char* _pstr;
};

// TODO 无需判空的写法
// String::String() : _pstr(new char[1]()) {}

String::String()
    : _pstr(nullptr)
{}

String::String(const char* str)
    : _pstr(new char[strlen(str) + 1]())
{
    strcpy(_pstr, str);
}

String::String(const String& str)
{
    if (_pstr) {
        delete[] _pstr;
        _pstr = nullptr;
    }
    _pstr = new char[strlen(str._pstr) + 1]();
    strcpy(_pstr, str._pstr);
}

String::~String()
{
    if (_pstr) {
        delete[] _pstr;
        _pstr = nullptr;
    }
}

String& String::operator=(const String& str)
{
    if (this->_pstr) {
        delete[] this->_pstr;
        this->_pstr = nullptr;
    }
    this->_pstr = new char[strlen(str._pstr) + 1]();
    strcpy(this->_pstr, str._pstr);
    return *this;
}

String& String::operator=(const char* str)
{
    if (this->_pstr) {
        delete[] this->_pstr;
        this->_pstr = nullptr;
    }
    this->_pstr = new char[strlen(str) + 1]();
    strcpy(this->_pstr, str);
    return *this;
}

String& String::operator+=(const String& str)
{
    int len = strlen(str._pstr) + 1;
    char* tmp = new char[len]();
    if (_pstr) {
        len += strlen(_pstr);
        delete[] tmp;
        tmp = new char[len]();
        strcpy(tmp, _pstr);
        strcat(tmp, str._pstr);
        delete[] _pstr;
        _pstr = nullptr;
    }
    else {
        strcpy(tmp, str._pstr);
    }
    // TODO 简化
    // _pstr = new char[len]();
    // strcpy(_pstr, tmp);
    // delete[] tmp;
    _pstr = tmp;
    return *this;
}

String& String::operator+=(const char* str)
{
    int len = strlen(str) + 1;
    char* tmp = new char[len]();
    if (_pstr) {
        len += strlen(_pstr);
        delete[] tmp;
        tmp = new char[len]();
        strcpy(tmp, _pstr);
        strcat(tmp, str);
        delete[] _pstr;
        _pstr = nullptr;
    }
    else {
        strcpy(tmp, str);
    }
    _pstr = tmp;
    return *this;
}

char& String::operator[](std::size_t index)
{
    return _pstr[index];
}

const char& String::operator[](std::size_t index) const
{
    return _pstr[index];
}

std::size_t String::size() const
{
    return strlen(_pstr);
}

const char* String::c_str() const
{
    return _pstr;
}

bool operator==(const String& s1, const String& s2)
{
    return !strcmp(s1._pstr, s2._pstr);
}

bool operator!=(const String& s1, const String& s2)
{
    return strcmp(s1._pstr, s2._pstr);
}

bool operator<(const String& s1, const String& s2)
{
    return strcmp(s1._pstr, s2._pstr) < 0;
}

bool operator>(const String& s1, const String& s2)
{
    return strcmp(s1._pstr, s2._pstr) > 0;
}

bool operator<=(const String& s1, const String& s2)
{
    return strcmp(s1._pstr, s2._pstr) <= 0;
}

bool operator>=(const String& s1, const String& s2)
{
    return strcmp(s1._pstr, s2._pstr) >= 0;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    os << str._pstr;
    return os;
}

std::istream& operator>>(std::istream &is, String& str)
{

    char tmp[10] = {0};
    int  i       = 0;
    char c;
    while (is.get(c) && c != ' ' && c != '\n') {
        tmp[i++] = c;
        if (i >= 8) {
            str += tmp;
            i = 0;
            memset(tmp, 0, 10);
        }
    }

    if (strlen(tmp)) {
        str += tmp;
    }
    return is;

    // if(str._pstr){
    //     delete [] str._pstr;
    //     str._pstr = nullptr;
    // }
    // std::vector<char> buffer;
    // char ch;
    // while((ch = is.get()) != '\n'){
    //     buffer.push_back(ch);
    // }
    // str._pstr = new char[buffer.size() + 1]();
    // strncpy(str._pstr, &buffer[0], buffer.size());
    // return is;
}

String operator+(const String& s1, const String& s2)
{
    String rst;
    rst += s1;
    rst += s2;
    return rst;
}
String operator+(const String& s1, const char* s2)
{
    String rst;
    rst += s1;
    rst += s2;
    return rst;
}
String operator+(const char* s1, const String& s2)
{
    String rst;
    rst += s1;
    rst += s2;
    return rst;
}

void String::print()
{
    std::cout << "_ptr = " << _pstr << std::endl;
}

int main(void)
{

    String s("abc");
    String a("123");

    String concat("concat");
    concat += concat;
    std::cout << concat << std::endl;

    const char x = s[1];
    std::cout << "index = " << x << std::endl;

    std::cout << s.size() << " " << s.c_str() << std::endl;
    std::cout << (s == a) << std::endl;
    std::cout << (s != a) << std::endl;
    std::cout << (s > a) << std::endl;
    std::cout << (s < a) << std::endl;
    std::cout << (s >= a) << std::endl;
    std::cout << (s <= a) << std::endl;

    String s1, s2, s3;

    std::cin >> s1 >> s2 >> s3;

    std::cout << s1 << " " << s2 << " " << s3 << std::endl;

    std::cout << a + "xyz" << std::endl;


    return 0;
}