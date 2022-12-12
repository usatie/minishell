#include <stdio.h>
int strncmp(const char *s1, const char *s2, size_t n)
{
    while (n && *s1 && *s2){
        if (*s1 != *s2)
            return (unsigned char)*s1 - (unsigned char)*s2;
        s1++;
        s2++;
        n--;
    }
    if (!n) return 0;
    if (*s1) return 1;
    return -1;
}
