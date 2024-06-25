#include <iostream>
#include <string>
using std::string;
class Student{
private:
    string _name;
    int _no;
    int _age;
public:
    Student(){}

    Student(const string& name, const int no = 1000000, const int age = 18) : 
    _name(name), 
    _no(no), 
    _age(age){}

    ~Student(){}

};
int main(){

    Student s1;
    Student s2("Join", 123654, 22);
    Student s3("Join", 123654);


}