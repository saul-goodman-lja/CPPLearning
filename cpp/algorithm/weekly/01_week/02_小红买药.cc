#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
using std::cin, std::cout, std::endl;
using std::vector, std::string;

void process(std::pair<long long, long long> &drug, long long &status){

    status = (status & (~drug.first)) | drug.second;
    cout << __builtin_popcount(status) << endl;
}

void getsNum(long long &status, int n){
    char c;
    for(int i = 0; i < n; i++){
        cin >> c;
        if(c =='1'){
            status += 1 << i;
        }
    }
}
int main(void){

    int n, m;
    long long status = 0;
    cin >> n;
    getsNum(status, n);
    cin >> m;
    vector<std::pair<long long, long long>> drug(m);
    for(int i = 0; i < m; i++){
        getsNum(drug[i].first, n);
        getsNum(drug[i].second, n);
    }
    int p;
    cin >> p;
    while(p--){
        int index;
        cin >> index;
        process(drug[index - 1], status);
    }

    return 0;
}