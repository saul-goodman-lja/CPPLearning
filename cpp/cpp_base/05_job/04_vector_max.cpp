#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using std::cin, std::cout, std::string, std::istringstream;
using std::vector, std::max_element, std::min_element;

int main(void){

    string line;
    char t;
    string other;
    getline(cin, line);
    istringstream iss(line);
    iss >> other >> t >> t;
    int num, n;
    vector<int> data;
    while(iss >> num >> t){
        data.push_back(num);
        if(t == ']'){
            break;
        }
    }

    while(iss >> t){
        if(t == '='){
            break;
        }
    }
    iss >> n;
    vector<int> temp;
    int rst = 0;
    for(auto & element : data){
        temp.push_back(element);
        if(temp.size() == n){
            rst = std::max(rst, *max_element(temp.begin(), temp.end()) - *min_element(temp.begin(), temp.end()));
            temp.erase(temp.begin());
        }
    }

    cout << rst << "\n";

    return 0;
}