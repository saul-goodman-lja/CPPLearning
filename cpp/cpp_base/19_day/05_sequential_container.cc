#include <iostream>
#include <vector>
#include <deque>
#include <list>

using std::cin, std::cout, std::endl;
using std::vector, std::deque, std::list;

void test1(){
    vector<int> v1;
    vector<int> v2(10);
    vector<int> v3(v2.begin(), v2.end());
    vector<int> v4(std::move(v3));
    vector<int> v5{10, 42};
    for(int t : v4){
        cout << t << " ";
    }
    cout << endl;
}

void test2(){
    deque<int> d1;
    deque<int> d2(10, 1);
    deque<int> d3(d2.begin(), d2.end());
    deque<int> d4(std::move(d3));
    deque<int> d5{10, 42};
    for(int t : d4){
        cout << t << " ";
    }
    cout << endl;
}

void test3(){
    list<int> l1;
    list<int> l2(10, 222);
    list<int> l3(l2.begin(), l2.end());
    list<int> l4(std::move(l3));
    list<int> l5{10, 42};
    for(int t : l4){
        cout << t << " ";
    }
    cout << endl;
}

int main(void){
    test1();
    test2();
    test3();
    return 0;
}