#include <iostream>
#include <set>
#include <algorithm>

using std::cin, std::cout, std::endl;
using std::set;

template <typename T>
T add(T a, T b){
    return a + b;
}   

template <typename T>
const T adder(const T a, const T b){
    return a + b;
}  

template <>
const set<int> adder<set<int>>(const set<int> a, const set<int> b){
    set<int> result;
    std::set_union(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.end()));
    return result;
}

void test(){
    set<int> a = {11, 12, 13, 14, 15};
    set<int> b = {1, 2, 3, 4, 5};
    cout << add(111, 222) << endl;
    cout << add(1.2, 3.4) << endl;
    
    set<int> c = adder(a, b);
    for(int t : c){
        cout << t << " ";
    }

}

int main(){
    test();
    return 0;
}
