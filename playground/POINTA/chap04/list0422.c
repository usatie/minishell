#include <stddef.h>
#include <stdio.h>

size_t strlen(const char *s)
{
    const char *p = s;

    while (*s)
        s++;
    return s - p;
}

int main()
{
    printf("%u\n", (unsigned int)(strlen("123")));
    return 0;
}
