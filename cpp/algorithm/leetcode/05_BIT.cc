#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

class BIT {
public:
    BIT(int n) : tree(n+1, 0) {}
    void add(int i){
        while(i < tree.size()){
            tree[i]++;
            i += i & -i;
        }
    }

    int pre(int i){
        int res = 0;
        while(i > 0){
            res += tree[i];
            i &= i - 1;
        }
        return res;
    }
private:
    std::vector<int> tree;
};

class Solution{
public:
    std::vector<int> resultArray(std::vector<int> &nums){
        auto sorted = nums;
        std::ranges::sort(sorted);
        sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());
        int m = sorted.size();

        std::vector<int> a{nums[0]}, b{nums[1]};
        BIT t1(m + 1), t2(m + 1);
        t1.add(std::ranges::lower_bound(sorted, nums[0]) - sorted.begin() + 1);
        t2.add(std::ranges::lower_bound(sorted, nums[1]) - sorted.begin() + 1);

        for(int i = 2; i < nums.size(); i++){
            int x = nums[i];
            int v = std::ranges::lower_bound(sorted, x) - sorted.begin() + 1;

            int gc1 = a.size() - t1.pre(v);
            int gc2 = b.size() - t2.pre(v);
            if(gc1 > gc2 || (gc1 == gc2 && a.size() <= b.size())){
                a.push_back(x);
                t1.add(v);
            }else{
                b.push_back(x);
                t2.add(v);
            }
        }
        a.insert(a.end(), b.begin(), b.end());
        return a;
    }
};