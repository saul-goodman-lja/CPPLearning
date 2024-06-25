#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using std::cout;
// g++ -std=c++17 stlpreview.cpp -o test
int main(void){

    std::vector<int> vec(20);
    std::generate(vec.begin(), vec.end(), rand);
    std::sort(vec.begin(), vec.end());
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, "\n"));
    return 0;
}