#include <iostream>
#include <limits>
#include <string>
using std::cin, std::cout, std::endl;
using std::istream, std::string;

void printStatus(istream & is){
    cout << is.good() << endl;
    cout << is.fail() << endl;
    cout << is.eof() << endl;
    cout << is.bad() << endl;
}

int main(void){


    int n;
    cin >> n;
    cout << "n = " << n << endl;
    printStatus(cin);
    cout << "--------" << endl;
    if(!cin.good()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        printStatus(cin);
    }

    string line;
    cin >> line;
    cout << "line = " << line << endl;


    return 0;
}