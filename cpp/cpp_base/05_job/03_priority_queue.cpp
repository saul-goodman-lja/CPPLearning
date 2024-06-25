#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
#include <algorithm>

using std::cin, std::cout, std::string, std::istringstream;
using std::vector, std::priority_queue;

struct customComparator{
    bool operator()(const int& a, const int& b){
        return a > b;
    }
};

void processData(priority_queue<int> &que, int n, const int element){
    vector<int> vec;
    while(!que.empty() && n--){
        if(element == que.top()){
            que.pop();
            break;
        }
        vec.push_back(que.top());
        que.pop();
    }
    for(auto & ele : vec){
        que.push(ele);
    }
}

void processData(priority_queue<int, vector<int>, customComparator>& que, int n, const int element){
    vector<int> vec;
    while(!que.empty() && n--){
        if(element == que.top()){
            que.pop();
            break;
        }
        vec.push_back(que.top());
        que.pop();
    }
    for(auto & ele : vec){
        que.push(ele);
    }
}

int main(void){
    priority_queue<int> bigQue;
    priority_queue<int, vector<int>, customComparator> smallQue;

    string line;
    char t;
    getline(cin, line);
    istringstream iss(line);
    iss >> line >> t >> t;
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
    int rst = 0;
    for(int i = 0; i < data.size(); i++){
        if(i >= n){
            processData(bigQue, n, data[i - n]);
            processData(smallQue, n, data[i - n]);
        }
        while(bigQue.size() && data[i] > bigQue.top()){
            bigQue.pop();
        }
        while(smallQue.size() && data[i] < smallQue.top()){
            smallQue.pop();
        }
        bigQue.push(data[i]);
        smallQue.push(data[i]);

        rst = std::max(rst, bigQue.top() - smallQue.top());
    }

    cout << rst << "\n";

    return 0;
}