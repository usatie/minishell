#include <stdio.h>

int main(void)
{
    int a[5];

    printf(" a    の値=%p\n",a);
    printf("&a[0] の値=%p\n",&a[0]);

    if(a == &a[0])
        puts("aと&a[0]は等しい");
    else
        puts("aと&a[0]は等しくない");

    return 0;
}