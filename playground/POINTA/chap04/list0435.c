#include <stddef.h>
#include <stdio.h>

char *strrchr(const char *s, int c)
{
    const char *p = NULL;

    c = (char)c;
    while (1){
        if (*s == c)
            p = s;
        if (*s == '\0')
            break;
        s++;
    }
    return (char *)p;
}

int main(void)
{
    const char *s = "123";
    int c = '2';
    printf("%s\n", strrchr(s, c));
    return 0;
}
