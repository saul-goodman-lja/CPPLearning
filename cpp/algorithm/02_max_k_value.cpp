#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#include <set>

using std::cout;
using std::endl;

// multiple set
// class Solution{

// public:
//     int findKthLargest(std::vector<int>& nums, int k){
//         auto customComparator = [](int a, int b){
//             return a > b;
//         };

//         std::multiset<int, decltype(customComparator)> order_set(customComparator);

//         for(int i = 0; i < nums.size(); i++){
//             order_set.insert(nums[i]);
//         }

//         auto it = order_set.begin();
//         std::advance(it, k-1); // 移动 k-1次
//         return *it;
//     }

// };

// priority_queue
class Solution{

public:
    int findKthLargest(std::vector<int>& nums, int k){

        auto customComparator = [](int a, int b){
            return a < b;
        };

        std::priority_queue<int, std::vector<int>, std::function<bool(int, int)>> priority_queue(customComparator);


        for(int i = 0; i < nums.size(); i++){
            priority_queue.push(nums[i]);
        }   

        int j = 1;
        while(j < k){
            priority_queue.pop();
            j++;
        }

        return priority_queue.top();

    }

};

int main(void){

    std::vector<int> vec = {3, 2, 1, 5, 6, 4};

    Solution solution;
    cout << solution.findKthLargest(vec, 2) << "\n";

    return 0;
}