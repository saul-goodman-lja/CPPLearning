#include <iostream>

class T
{
private:
    int* arr = new int[5];

public:
    T()
    {
        for (int i = 0; i < 5; i++) {
            arr[i] = i;
        }
    }
};

int main()
{

    int  example[5];
    int* ptr = example;

    example[2]              = 5;
    *(int*)((char*)ptr + 8) = 6;

    int* p = new int[5];
    delete[] p;

    std::cout << "";
}