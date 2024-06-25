#include <iostream>
#include <string>
#include <sstream>
#include <deque>
#include <vector>
#include <algorithm>

using std::cin, std::cout, std::string, std::istringstream;
using std::vector, std::deque;

// get the max value of data
class MyBigQueue{ // big to small
public:
    deque<int> que;

    void pop(int value){
        if(!que.empty() && value == que.front()){
            que.pop_front();
        }
    }

    void push(int value){
        while(!que.empty() && value > que.back()){
            que.pop_back();
        }
        que.push_back(value);
    }

    int front(){
        return que.front();
    }
};

class MySmallQueue{
public:
    deque<int> que;

    void pop(int value){
        if(!que.empty() && value == que.front()){
            que.pop_front();
        }
    }

    void push(int value){
        while(!que.empty() && value < que.back()){
            que.pop_back();
        }
        que.push_back(value);
    }

    int front(){
        return que.front();
    }
};

int main(void){

    string line;
    getline(cin, line);
    string other;
    char t;
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
    MyBigQueue bigQue;
    MySmallQueue smallQue;
    int rst = 0;
    for(int i = 0; i < data.size(); i++){
        if(i >= n){
            bigQue.pop(data[i - n]);
            smallQue.pop(data[i - n]);
        }
        bigQue.push(data[i]);
        smallQue.push(data[i]);
        rst = std::max(rst, bigQue.front() - smallQue.front());
    }

    cout << rst << "\n";
    return 0;
}