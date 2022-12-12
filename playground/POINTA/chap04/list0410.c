#include <stdio.h>

int main(void)
{
    char *p = "123";

    printf("p = \"%s\"\n", p);

    p = "456";

    printf("p = \"%s\"\n", p);

    return 0;
}
