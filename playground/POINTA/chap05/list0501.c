#include <stdio.h>

int main(void)
{
    int i;
    char a[][5] = {"LISP", "C", "Ada"};

    for (i = 0; i < 3; i++)
        printf("a[%d] = \"%s\"\n", i, a[i]);
    return 0;
}
