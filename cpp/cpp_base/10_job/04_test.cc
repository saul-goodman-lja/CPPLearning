#include <iostream>
#include <map>

using std::cin, std::cout, std::endl;
using std::map;

int main(void){
    
    map<int, int> count_map;
    int n, x;
    cin >> n >> x;
    
    for(int i = 0 ; i < n; i++){
        int t;
        cin >> t;
        count_map[t]++;
    }
    auto it = count_map.lower_bound(x);
    
    cout << std::prev(it, 1)->second << endl;
    
    return 0;
}