#include <iostream>
#include <string.h>

using std::cin, std::cout, std::endl;
using std::size_t, std::ostream;

class CowString{

    class CharProxy{
    public:
        CharProxy(CowString &self, size_t idx) : _self(self), _idx(idx){}
        
        char & operator=(const char);

        operator char(){
            cout << "operate char" << endl;
            return _self._pstr[_idx];
        }

        friend ostream & operator<<(ostream &, const CharProxy &);

    private:
        CowString &_self;
        size_t _idx;
    };

public:
    CowString();
    CowString(const char *);
    CowString(const CowString &);
    CowString & operator=(const CowString &);
    ~CowString();

    size_t size() const{
        return strlen(_pstr);
    }

    const char *c_str(){
        return _pstr;
    }

    int useCount(){
        return *reinterpret_cast<int*>(_pstr - kRefcountLength);
    }

    CharProxy operator[](size_t);

    friend ostream & operator<<(ostream &, const CowString &);

    friend ostream & operator<<(ostream &, const CharProxy &);


private:
    char * malloc(const char *pstr = nullptr){
        if(pstr){
            return new char[1 + strlen(pstr) + kRefcountLength]() + kRefcountLength;
        }else{
            return _pstr = new char[1 + kRefcountLength]() + kRefcountLength;
        }
    }

    void initRefcount(){
        *(_pstr - kRefcountLength) = 1;
    }

    void increaseRefcount(){
        ++*(_pstr - kRefcountLength);
    }
    
    void decreaseRefcount(){
        --*(_pstr - kRefcountLength);
    }

    void release(){
        decreaseRefcount();
        if(useCount() == 0){
            delete [] (_pstr - kRefcountLength);
        }
        _pstr = nullptr;
    }

private:
    char *_pstr;
    static const int kRefcountLength = sizeof(int);
};

CowString::CowString() : _pstr(malloc()) {
    initRefcount();
}

CowString::CowString(const char *pstr) : _pstr(malloc(pstr)) {
    initRefcount();
    strcpy(_pstr, pstr);
}

CowString::CowString(const CowString &rhs) : _pstr(rhs._pstr) {
    increaseRefcount();
}

CowString & CowString::operator=(const CowString &rhs){
    if(this != &rhs){
        release();
        _pstr = rhs._pstr;
        increaseRefcount();
    }
    return *this;
}

CowString::~CowString(){
    release();
}

CowString::CharProxy CowString::operator[](size_t idx){

    return CowString::CharProxy(*this, idx);
}

ostream & operator<<(ostream & os, const CowString &rhs){
    os << rhs._pstr;
    return os;
}

char & CowString::CharProxy::operator=(const char c){
    cout << "operate write" << endl;
    if(_idx >= 0 && _idx < _self.size()){
        if(_self.useCount() > 1){
            _self.decreaseRefcount();
            char *ptmp = _self.malloc(_self._pstr);
            strcpy(ptmp, _self._pstr);
            _self._pstr = ptmp;
            _self.initRefcount();
        }
        _self._pstr[_idx] = c;
        return _self._pstr[_idx];
    }else{
        cout << "out of range" << endl;
        static char nullchar = '\0';
        return nullchar;
    }
}

ostream & operator<<(ostream & os, const CowString::CharProxy &rhs){
    cout << "operate <<" << endl;
    if(rhs._idx >= 0 && rhs._idx < rhs._self.size()){
        os << rhs._self._pstr[rhs._idx];
    }else{
        os << "out of range";
    }
    return os;
}


void test0(){

    CowString str1;
    CowString str2 = str1;

    cout << str1.useCount() << endl;

    CowString str3 = "hello";
    char c = str3[0];
    str1 = str3;
    cout << str3.useCount() << endl;
    (str1[0] = 'A') = 'a';
    cout << str1[0] << endl;
    cout << str1[1] << endl;
    cout << str3.useCount() << endl;
}


int main(void){
    test0();
    return 0;
}