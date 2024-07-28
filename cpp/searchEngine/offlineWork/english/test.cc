#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using std::cin, std::cout;
using std::map, std::set;
using std::ofstream, std::ifstream;
using std::string;
using std::istringstream;

int main(){
    ifstream ifs("../dictIndex.dat");
    if(!ifs.is_open()){
        cout << "file not found" << std::endl;
        return 0;
    }
    string line;
    int i = 0;
    while(std::getline(ifs, line)){
       cout << i++ << "\n";
    }
}