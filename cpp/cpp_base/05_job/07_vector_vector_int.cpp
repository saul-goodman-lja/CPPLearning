#include <iostream>
#include <vector>

using std::cin, std::cout, std::endl;
using std::vector;

int main(void){

    vector<vector<int>> data(10);

    int n = 10;
    for(auto & element : data){
        // cout << element.size() << endl;
        // cout << element.capacity() << endl;
        for(int i = 0; i < n; i++){
            element.push_back(i);
        }
        n--;
    }

    for(auto & vec : data){
        for(auto it = vec.begin() ; it != vec.end(); it++){
            cout << *it << " ";
        }
        cout << endl;
    }

    return 0;
}