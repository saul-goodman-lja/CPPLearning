#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

template <typename  Container>
void display(const Container &con)
{
    for(auto &elem : con)
    {
        cout << elem << "  ";
    }
    cout << endl;
}

void test()
{
    cout << "sizeof(vector<int>) = " << sizeof(vector<int>) << endl;
    cout << "sizeof(vector<long>) = " << sizeof(vector<long>) << endl;
    vector<int> number = {1, 3, 5, 7, 9, 8, 6, 4, 2, 10};
    display(number);

    cout << endl << "在vector的尾部进行插入与删除" << endl;
    number.push_back(100);
    number.push_back(200);
    display(number);
    number.pop_back();
    display(number);

    //没有在vector的头部提供插入与删除的方法？
    //因为vector是一端开口的，如果在头部插入一个元素，那么
    //后面的元素都会后移一个存放新插入的元素；如果在头部
    //删除一个元素，后面的元素都会向前移动一个，那么时间
    //复杂度比较高O(N)

    cout << endl << "在vector的任意位置插入元素" << endl;
    auto it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    number.insert(it, 300);
    display(number);
    cout << "*it = " << *it << endl;
    cout << "size = " << number.size() << endl;
    cout << "address  " << &(*it) << endl;
    cout << "&number[0]  " << &number[0] << endl;

    cout << endl;
    number.insert(it, 10, 55);
    display(number);
    cout << "*it = " << *it << endl;
    cout << "size = " << number.size() << endl;
    cout << "address  " << &(*it) << endl;
    cout << "&number[0]  " << &number[0] << endl;

    cout << endl;
    // vector<int> vec = {12, 34, 56, 78};
    // number.insert(it, vec.begin(), vec.end());
    // display(number);
    // cout << "*it = " << *it << endl;

    // cout << endl;
    // number.insert(it, {666, 888, 999});
    // display(number);
    // cout << "*it = " << *it << endl;
}

int main(int argc, char *argv[])
{
    test();
    /* vector<int> vec; */
    /* vec[0] = 100; */
    return 0;
}

