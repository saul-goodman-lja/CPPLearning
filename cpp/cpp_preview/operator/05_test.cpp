#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        auto comparator = [] (int a, int b) { return a < b ;};
        sort(rewardValues.begin(), rewardValues.end(), comparator);
        int max_val = rewardValues[rewardValues.size() - 1];
        int ret = 0;
        rewardValues.pop_back();

        for(int i = 0; i < rewardValues.size(); i++){
            auto it = lower_bound(rewardValues.begin(), rewardValues.end(), max_val - rewardValues[i], 
            comparator);
            if(rewardValues[i] >= *it){
                break;
            }
            if(it != rewardValues.end() && *it <= max_val - rewardValues[i]){
                cout << *it << endl;
                it = prev(it, 1);
                ret = max(ret, *it + rewardValues[i]);
                cout << *it << endl;
            }else{
                ret = max(ret, rewardValues[i]);
            }
        }
        return ret + max_val;
    }
};

int main() {
    Solution sol;
    
    std::vector<int> testCase1 = {1,6,4,3,2};
    int result1 = sol.maxTotalReward(testCase1);
    std::cout << "Test case 1 result: " << result1 << std::endl;

    // 添加更多测试用例...

    return 0;
}