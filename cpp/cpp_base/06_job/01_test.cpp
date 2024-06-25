#include <iostream>

using std::cin, std::cout;

int main(void){


    char a[200] = {0};
    cin.getline(a, 200, ' ');
    cout << a;

    return 0;
}