#include <iostream>
#include <vector>
#include <functional>

using std::cin, std::cout, std::endl;
using std::vector;

template <typename T, typename Compare = std::less<T>>
class MyQsort{
public:
    MyQsort(T *, size_t , Compare);
    void quick(int, int, Compare&);
    int partition(int, int, Compare&);
    void print();
private:
    vector<T> _vec;
};

template <typename T, typename Compare>
MyQsort<T, Compare>::MyQsort(T *arr, size_t len, Compare com) 
    : _vec(arr, arr + len){
        quick(0, len - 1, com);
    }

template <typename T, typename Compare>
void MyQsort<T, Compare>::quick(int left, int right, Compare& com){
    if(left >= right){
        return ;
    }
    int pivot_idx = partition(left, right, com);
    quick(left, pivot_idx - 1, com);
    quick(pivot_idx + 1, right, com);
}

template <typename T, typename Compare>
int MyQsort<T, Compare>::partition(int left, int right, Compare& com){
    // int pivot = _vec[left];
    // int low = left, high = right;
    // while(low < high){
    //     while(low < high && !com(_vec[high], pivot)){
    //         high--;
    //     }
    //     _vec[low] = _vec[high];

    //     while(low < high && com(_vec[low], pivot)){
    //         low++;
    //     }
    //     _vec[high] = _vec[low];
    // }
    // _vec[low] = pivot;
    // return low;
    T pivot = _vec[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (com(_vec[j], pivot)) {
            i++;
            std::swap(_vec[i], _vec[j]);
        }
    }

    std::swap(_vec[i + 1], _vec[right]);
    return i + 1;
}

template <typename T, typename Compare>
void MyQsort<T, Compare>::print(){
    for(auto &e : _vec){
        cout << e << " ";
    }
    cout << endl;
}
void test(){
    int arr[] = {1, 3, 5, 2, 4, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    MyQsort<int, std::less<int>> less(arr, n, std::less<int>());
    less.print();
    auto com = [](const int& a, const int& b) { return a > b; };
    MyQsort<int, decltype(com)> greater(arr, n, com);
    // 模版 和 lambda 解析顺序可能会冲突
    // MyQsort<int, decltype([](const int& a, const int& b) { return a > b; })> greater(arr, n, [](const int& a, const int& b) { return a > b; });
    greater.print();
}

int main(){
    test();
    return 0;
}
