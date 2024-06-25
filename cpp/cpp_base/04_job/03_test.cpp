#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <deque>
using std::cin, std::cout;
using std::vector, std::deque;
using std::string, std::istringstream;
int main(void){

    string line;
    string other;
    char t;
    int n;
    deque<int> dq;
    getline(cin, line);
    istringstream iss(line);
    iss >> other >> t >> t;
    while(iss >> n >> t){
        dq.push_back(n);
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
    vector<int> vec;
    vector<int> temp;
    for(const int& element : dq){
        temp.push_back(element);
        if(temp.size() == n){
            int x = *std::max_element(temp.begin(), temp.end()) - *std::min_element(temp.begin(), temp.end());
            vec.push_back(x);
            temp.erase(temp.begin());
        }
    }

    cout << *std::max_element(vec.begin(), vec.end()) << "\n";

    return 0;
}