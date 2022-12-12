#include <stdio.h>

int main(void)
{
    char s[] = "ABC";

    printf("s = \"%s\"\n", s);

    s = "DEF";

    printf("s = \"%s\"\n", s);

    return 0;
}
