#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

using std::cin, std::cout, std::endl;
using std::vector;

class Fenwick {
public:
    Fenwick(int n) : tree(n) {}
    void add(int i){
        while(i < tree.size()){
            tree[i]++;
            i += i & -i;
        }
    }
    // 优化 i &= i-1
    int pre(int i){
        int res = 0;
        while(i > 0){
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }

private:
    vector<int> tree;
};

class Solution {
public:
    /**
     * 根据给定的整数数组，返回一个结果数组，该数组是将原数组中的元素排序并去重后的结果，
     * 并且满足：如果结果数组中某个元素的出现次数大于等于数组中另一个元素的出现次数，
     * 那么原数组中前者第一次出现的索引不高于后者第一次出现的索引。
     * 
     * @param nums 原始整数数组
     * @return 排序并去重后的结果数组
     */
    vector<int> resultArray(vector<int> &nums){
        // 创建一个排序后的副本，用于后续处理
        auto sorted = nums;
        std::ranges::sort(sorted);
        // 去除排序后数组中的重复元素
        sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());
        int m = sorted.size();

        // 初始化两个辅助数组a和b，分别用于存放两种策略下的元素
        vector<int> a{nums[0]}, b{nums[1]};
        // 初始化两个Fenwick树，用于高效计算前缀和
        Fenwick t1(m + 1), t2(m + 1);
        // 在Fenwick树中添加初始元素的位置信息
        t1.add(std::ranges::lower_bound(sorted, nums[0]) - sorted.begin() + 1);
        t2.add(std::ranges::lower_bound(sorted, nums[1]) - sorted.begin() + 1);
        for(int i = 2; i < nums.size(); i++){
            int x = nums[i];
            int v = std::ranges::lower_bound(sorted, x) - sorted.begin() + 1;
            // 计算在数组a和b中，元素出现次数的差值
            int gc1 = a.size() - t1.pre(v);
            int gc2 = b.size() - t2.pre(v);
            // 根据差值和数组大小决定将当前元素添加到a还是b中
            if(gc1 > gc2 || (gc1 == gc2 && a.size() <= b.size())){
                a.push_back(x);
                t1.add(v);
            }else{
                b.push_back(x);
                t2.add(v);
            }
        }
        // 将b中的元素合并到a中，形成最终的结果数组
        a.insert(a.end(), b.begin(), b.end());
        return a;
    }
};

void test(){
    Solution s;
    // 按照上述样例，生成乱序复杂的新样例
    for(int i = 0; i < 2; i++){
        int n = rand() % 10 + 1;
        vector<int> nums(n);
        for(int j = 0; j < n; j++){
            nums[j] = rand() % 1000 + 1;
        }
        vector<int> rst = s.resultArray(nums);
        for(auto & ele : rst){
            cout << ele << " "; 
        }
        cout << endl;
    }
}

void test1(){
    Fenwick t(10);
    for(int i = 1; i <= 10; i++){
        t.add(i);
    }



    t.add(5);
    // t.add(9);
    cout << t.pre(5) << endl;
    cout << t.pre(6) << endl;
    cout << t.pre(8) << endl;

}

auto main() -> int{
    
    test1();
    return 0;
}