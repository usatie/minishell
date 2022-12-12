#include <stddef.h>
#include <stdio.h>
char *strchr(const char *s, int c)
{
    c = (char)c;
    while (*s != c) {
        if (*s == '\0')
            return NULL;
        s++;
    }
    return (char *)s;
}

int main(void)
{
    const char *s="ABC";
    int c = 'B';
    printf("%s\n", strchr(s, c));
    return 0;
}
