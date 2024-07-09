#include <iostream>
#include <list>
#include <string>
#include <memory>

using std::cin, std::cout, std::endl;
using std::list;
using std::string;
using std::unique_ptr;

class Observer;
class Subject{
public:
    virtual void attach(Observer *) = 0;
    virtual void detach(Observer *) = 0;
    virtual void notify() = 0;
    virtual ~Subject(){}  
};

class ConcreateSubject : public Subject{
public:
    void attach(Observer *) override;
    void detach(Observer *) override;
    void notify() override;
    void setStatus(int status){
        _status = status;
    }
    int getStatus(){
        return _status;
    }
private:
    list<Observer *> _obList;
    int _status;
};

class Observer{
public:
    virtual void update(int) = 0;
    virtual ~Observer(){}
};

class ConcreteObserver1
: public Observer{
public:
    ConcreteObserver1(const string& name)
    : _name(name){}
    void update(int status) override{
        cout << "ConcreteObserver1::update() status = " << status << endl;
    }
private:
    string _name;
};

class ConcreateObserver2
: public Observer{
public:
    ConcreateObserver2(const string& name)
    : _name(name){}
    void update(int status) override{
        cout << "ConcreateObserver2::update() status = " << status << endl;
    }
private:
    string _name;
};

void ConcreateSubject::attach(Observer *ob){
    if(ob){
        _obList.emplace_back(ob);
    }
}
void ConcreateSubject::detach(Observer *ob){
    if(ob){
        _obList.remove(ob);
    }
}
void ConcreateSubject::notify(){
    for(auto ob : _obList){
        ob->update(_status);
    }
}

void test0(){
    auto pSubject = std::make_unique<ConcreateSubject>();
    auto ob1 = std::make_unique<ConcreteObserver1>("ob1");
    auto ob2 = std::make_unique<ConcreateObserver2>("ob2");

    pSubject->attach(ob1.get());
    pSubject->attach(ob2.get());
    pSubject->setStatus(1745);
    pSubject->notify();
    
}


int main(void){

    test0();

    return 0;
}