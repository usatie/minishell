#include <stdio.h>

int main(void)
{
    int i;
    int a[5] = {1, 2, 3, 4, 5};
    int *p = a;

    for (i = 0; i < 5; i++)
    {
        printf ("a[%d]     = %d\n", i, a[i]);
        printf ("*(a + %d) = %d\n", i, *(a + i));
        printf ("p[%d]     = %d\n", i, p[i]);
        printf ("*(p + %d) = %d\n\n", i, *(p + i));
    }
    for (i = 0; i < 5; i++)
    {
        printf ("a[%d]     = %p\n", i, &a[i]);
        printf ("*(a + %d) = %p\n", i, (a + i));
        printf ("p[%d]     = %p\n", i, &p[i]);
        printf ("*(p + %d) = %p\n\n", i, (p + i));
    }
    return 0;
}