#include <iostream>
#include <sstream>
#include <string>

using std::cin, std::cout, std::endl;
using std::string, std::istringstream;

bool isNum(const string & str){
    if(str[0] == 'e' || str[str.size() - 1] == 'e' || str[0] == '.' || str[str.size() - 1] == '.'){
        return false;
    }
    istringstream iss(str);
    double num;
    iss >> num;
    if(!iss.eof()){
        iss.clear();
        return false;
    }
    iss.clear();
    cout << "num = " << num << ", ";
    return true;
}

int main(void){

    string str;
    while(cin >> str){
        if(isNum(str)){
            cout << str << " is a num" << endl;
        }else{
            cout << str << " is not a num" << endl;
        }
    }
    return 0;
}