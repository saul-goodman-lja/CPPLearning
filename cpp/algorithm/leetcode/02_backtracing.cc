#include <iostream>
#include <vector>
using std::cin, std::cout;
using std::vector;

class Solution {
    vector<vector<int>> rst;
    vector<int> path;
public:
    vector<vector<int>> combine(int n, int k) {
        int startIdx = 1;
        path.reserve(n);
        int size = 1;
        for(int i = 0; i < k; i++){
            size *= (n - i);
            size /= (i + 1);
        }
        rst.reserve(size);
        backtracing(n, k, startIdx);
        return rst;
    }

    void backtracing(int n, int k, int startIdx){
        // if(path.size() + (n - startIdx + 1) < k){
        //     return ;
        // }
        if(path.size() == k){
            rst.emplace_back(path);
            return;
        }
        for(int i = startIdx; i <= n - (k - path.size() - 1); i++){
            path.emplace_back(i);
            backtracing(n, k, i + 1);
            path.pop_back();
        }
    }

};


int main(void){

    Solution s;
    vector<vector<int>> rst;
    rst = s.combine(4, 2);

    return 0;
}



