#include <stdio.h>

void put_string_array(const char *s[], int n)
{
    printf("s[%d] = \"%s\"\n", n, s[n]);
}


int main(void)
{
    int i;
    char *p[] = {"PAUL", "X", "MAC"};
    int np = sizeof(p) / sizeof(p[0]);

    for (i = 0; i < np; i++)
        put_string_array(p, i);
    return 0;
}
