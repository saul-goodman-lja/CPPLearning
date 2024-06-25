#include <iostream>
#include <vector>

using std::cin, std::cout, std::endl;
using std::vector;

int main(){
    vector<int> num{1, 2, 3};
    num.resize(7);
    cout << num.capacity() << endl;
}