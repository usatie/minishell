#include <stdio.h>
#include <string.h>

int main(void)
{
    char m[] = "1234567890\0ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char tmp[128];
    int ch;
    char *p;

    printf("探す文字は:");
    scanf("%s", tmp);
    ch = tmp[0];

    if ((p = memchr(m, ch, sizeof(m))) == NULL)
        printf("文字'%c'は存在しません\n", ch);
    else
        printf("文字'%c'は%ld文字目に存在します\n", ch, (long)(p - m)+ 1);
    return 0;
}
