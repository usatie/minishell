#include <stdio.h>

char *strncpy(char *s1, const char *s2, size_t n)
{
    char *p = s1;

    while (n) {
        n--;
        if (!(*s1++ = *s2++)) break;
    }

    while (n--)
        *s1++ = '\0';

    return p;
}

int main(void)
{
    const char *s1 = "123";
    char s2[128];
    char *ret = strncpy(s2, s1, 5);

    printf("s1 = %s, s2 = %s, ret = %s\n", s1, s2, ret);
    return 0;
}
