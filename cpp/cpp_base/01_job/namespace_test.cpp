#include <iostream>

int num = 100;

using std::cin;
using std::cout;
using std::endl;

namespace  wd {
    int num = 10;
}

// void test(){
//     int num = 5;
//     using wd::num;
//     cout << num << endl;
// }
void test1(){
    int num = 5;
    using namespace wd;
    cout << num <<endl;
}

int foo(int x,int y)
{
    if(x <= 0 ||y <= 0)
        return 1;
    return 3 * foo(x-1, y/2);
}

void func(){
    int a[5]={1,2,3,4,5};
    int *ptr=(int *)(&a + 1);
    int (*p)[5] = &a;
    printf("%d,%d",*(a + 1),*(ptr - 1));
}

int main(void){

    cout << foo(3,5) << endl;
    func();

    int *a = new int();
    delete a;
    a = nullptr;

    return 0;
}