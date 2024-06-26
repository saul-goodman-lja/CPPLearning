#include <iostream>
#include <functional>
#include <vector>

using std::cin, std::cout, std::endl;
using std::vector;

template <typename T, typename Compare = std::less<T>>
class HeapSort{
public:
    HeapSort(T *arr, size_t size);
    void heapAdjust(size_t, size_t);
    void sort();
    void print();
private:
    vector<T> _vec;
    Compare _cmp;
};

template <typename T, typename Compare>
HeapSort<T, Compare>::HeapSort(T *arr, size_t size)
    : _vec(arr, arr + size) {
        int last_idx = (size - 2) >> 1;
        for (int i = last_idx; i >= 0; --i) {
            heapAdjust(i, size);
        }
        // print();
    }

template <typename T, typename Compare>
void HeapSort<T, Compare>::heapAdjust(size_t i, size_t size) {
    while(1){
        int lchild_idx = (i << 1) + 1;
        int rchild_idx = (i << 1) + 2;
        int max_idx = i;
        if(lchild_idx < size && _cmp(_vec[max_idx], _vec[lchild_idx])){
            max_idx = lchild_idx;
        }
        if(rchild_idx < size && _cmp(_vec[max_idx], _vec[rchild_idx])){
            max_idx = rchild_idx;
        }
        if(max_idx != i){
            std::swap(_vec[i], _vec[max_idx]);
            i = max_idx;
        }else{
            break;
        }
    }
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::sort()
{   
    int heap_len = _vec.size();
    while(heap_len){
        std::swap(_vec[0], _vec[heap_len - 1]);
        heap_len--;
        heapAdjust(0, heap_len);
    }
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::print(){
    for(auto i : _vec){
        std::cout << i << " ";
    }
    cout << endl;
}
void test(){
    int a[] = {55,2,6,4,7,8,5,2,3,1,9,0};
    int len = sizeof(a) / sizeof(a[0]);
    HeapSort<int> hs(a, len);
    hs.sort();
    hs.print();

    HeapSort<int, std::greater<int>> hs2(a, len);
    hs2.sort();
    hs2.print();
}
int main(void){
    test();
    return 0;
}