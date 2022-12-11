#include <stdio.h>

void put_str(const char *s)
{
    while (*s)
        putchar(*s++);
}

int main (void)
{
    char str[128];
    printf("文字列を入力してください:");
    scanf("%s", str);

    put_str(str);
    putchar('\n');

    return 0;
}
