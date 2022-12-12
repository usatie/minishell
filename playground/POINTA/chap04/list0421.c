#include <stddef.h>
#include <stdio.h>

size_t strlen(const char *s)
{
    size_t len = 0;

    while (*s++)
        len++;
    return len;
}

int main()
{
    printf("%u\n", (unsigned int)(strlen("123")));
    return 0;
}
