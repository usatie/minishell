#include <stdio.h>

int main(void)
{
    int a[4][3];

    printf("sizeof(a)        = %u\n", (unsigned)sizeof(a));
    printf("sizeof(a[0])     = %u\n", (unsigned)sizeof(a[0]));
    printf("sizeof(a[0][0])  = %u\n", (unsigned)sizeof(a[0][0]));

    printf("配列aは%d行%d列の二次元配列です\n",
        (int)(sizeof(a)   / sizeof(a[0])),
        (int)(sizeof(a[0])/ sizeof(a[0][0])));
    printf("構成要素は%d個です\n",
        (int)(sizeof(a)   / sizeof(a[0][0])));
    return 0;
}
