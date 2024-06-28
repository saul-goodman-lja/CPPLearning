#include <iostream>
#include <vector>
#include <deque>
#include <utility>
#include <set>

using std::cin, std::cout, std::endl;
using std::vector, std::deque;
using std::pair;
using std::set;

int main(void){
    
    set<long> ans;
    int M;
    cin >> M;
    vector<int> id(M);
    for(int i = 0; i < M; i++){
        cin >> id[i];
    }
    int Neighbour;
    
    cin >> Neighbour;

    long tb;
    int size;
    for(int i = 0; i < Neighbour; i++){
        cin >> tb >> size;
        int t;
        for(int j = 0; j < size; j++){
            cin >> t;
            for(int k = 0; k < id.size(); k++){
                if(t == id[k]){
                    ans.insert(tb);
                }
            }
        }
    }
    cout << ans.size() << endl;
    for(long t : ans){
        cout << t << " ";
    }
    cout << endl;
    
    return 0;
}