#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <vector>
// #include <stream>

using std::cout, std::cin, std::endl, std::flush, std::string;
using std::istringstream, std::ostringstream;
using std::istringstream, std::ostream;

int stringToInteger(const string& s);
int mindlessWork();
void bufferedExperiemnt(ostream& oss);
void printStateBits(const istringstream&);


void printStateBits(const istringstream& iss){
    cout << (iss.good() ? "G" : "-"); // G
    cout << (iss.fail() ? "F" : "-"); // fail
    cout << (iss.eof() ? "E" : "-"); // eof
    cout << (iss.bad() ? "B" : "-"); // bad
    cout << endl;
} 

int stringToInteger(const string& s){
    istringstream iss(s);
    // printStateBits(iss);

    int ret;
    iss >> ret;
    if(iss.fail()) throw std::domain_error("no value int at beginning!");
   
    if(!iss.eof()) throw std::domain_error("no more than a single valid int!");
    // printStateBits(iss);

    return ret;
}

void stringToIntergerTest(){
    while(true){
        cout << "Type in an integer: ";
        string s;
        if(!std::getline(cin, s)){
            throw std::domain_error("getline failed");
        }
        cout << "your typed in: "<< s << "\n";
        int rst = stringToInteger(s);
        cout << "As an integer , this is: " << rst <<"\n";
        cout << "Half of that is: " << rst / 2 << "\n";
    }
}

int main(void){

    std::ostringstream oss("Ito-En Green Tea", std::stringstream::ate);
    cout << oss.str() << endl;
    // oss << "16 .9 Ounces";
    oss << 16.9 << " Ounces";
    cout << oss.str() <<endl;

    // input 
    istringstream iss("16.9 Ounces");
    int amount;
    string unit;

    iss >> amount >> unit;
    iss >> unit;

    cout << amount/2 <<endl;
    cout << unit << endl;

    stringToIntergerTest();


    return 0;
}