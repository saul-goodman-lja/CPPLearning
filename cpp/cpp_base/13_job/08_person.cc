#include <iostream>
#include <cstring>
#include <iomanip>
#include <utility>

using std::cin, std::cout, std::endl;

class Person{
public:
    Person(const char *name = "unknown", const int age = -1) :
        _name(new char[strlen(name) + 1]()),
        _age(age){
            strcpy(_name, name);
    }

    Person(const Person &rhs) 
    : _name(new char[strlen(rhs._name) + 1]())
    , _age(rhs._age){
        strcpy(_name, rhs._name);
    }

    ~Person(){
        if(_name){
            delete [] _name;
            _name = nullptr;
        }
    }

    Person & operator=(const Person & rhs){
        if(this != &rhs){
            if(_name){
                delete [] _name;
                _name = nullptr;
            }
            _name = new char[strlen(rhs._name) + 1]();
            strcpy(_name, rhs._name);
            _age = rhs._age;
        }
        return *this;
    }

    void display(){
        cout << "name: " << _name << endl;
        cout << "age: " << _age << endl;
    }

private:
    char *_name;
    int _age;
};

class Employee : public Person{
public:
    Employee(const char *name = "unknown", int age = -1, const char *department = "unknown", const double salary = -1) : 
        Person(name, age),
        _department(new char[strlen(department) + 1]()),
        _salary(salary) {
            strcpy(_department, department);
            salaryCnt.first += _salary;
            salaryCnt.second++;
    }
    
    Employee(const Employee & rhs)
    : Person(rhs)
    , _department(new char[strlen(rhs._department) + 1]())
    , _salary(rhs._salary){
        strcpy(_department, rhs._department);
        salaryCnt.first += _salary;
        salaryCnt.second++;
    }
    
    ~Employee(){
        if(_department){
            delete [] _department;
            _department = nullptr;
        }
        salaryCnt.first -= _salary;
        salaryCnt.second--;
    }

    Employee & operator=(const Employee & rhs){
        if(this != &rhs){
            salaryCnt.first -= _salary;
            Person::operator=(rhs);
            if(_department){
                delete [] _department;
                _department = nullptr;
            }
            _department = new char[strlen(rhs._department) + 1]();
            strcpy(_department, rhs._department);
            _salary = rhs._salary;
            salaryCnt.first -= _salary;
        }
        return *this;
    }

    void display(){
        Person::display();
        cout << "department: " << _department << endl;
        cout << "salary: " << std::fixed << std::setprecision(2) << _salary << endl;
    }

    void printAverageSalary(){
        cout << "Average Salary: " << std::fixed << std::setprecision(2) << salaryCnt.first / salaryCnt.second << endl;
    }
private:
    char *_department;
    double _salary;
    static std::pair<double, int> salaryCnt;
};

std::pair<double, int> Employee::salaryCnt = std::make_pair(0, 0);

void test0(){
    Employee e("lja", 22, "cpp", 18888);
    e.display();

    Employee e2("xxx", 25, "java", 8888);
    e2.display();

    e.printAverageSalary();
}

int main(void){

    test0();

    return 0;
}