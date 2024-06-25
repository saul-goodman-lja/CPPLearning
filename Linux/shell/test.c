#include <stdio.h>

int main()
{   
    int a;
    a=10;
    int *b = (int *)&a;
    a=20;
    a=30;
    printf("Hello world\n");
    return 0;
}
