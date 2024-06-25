#include <iostream>
#include <vector>
#include <string>
#include <functional>

using namespace std;

class Solution {
    string MAPPING[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"}; 
public:
    vector<string> letterCombinations(string digits) {
        vector<string> rst;
        int n = digits.size();
        if(n == 0){
            return rst;
        }
        string path(n, 0);
        function<void(int)> dfs = [&](int i) -> void {
            if(i == n){
                rst.emplace_back(path);
                return ;
            }
            for(char c : MAPPING[digits[i] - '0']){
                path[i] = c;
                dfs(i + 1);
            }
        };
        dfs(0);
        return rst;
    }
};

void test0(){
    Solution s1;
    vector<string> vec = s1.letterCombinations("234");
    for(string str : vec){
        cout << str << endl;
    }
}

int main(void){

    test0();
    return 0;
}