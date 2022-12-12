#include <stdio.h>

int main(void)
{
    char str[4];

    str[0] = 'A';
    str[1] = 'B';
    str[2] = 'C';
    str[3] = '\0';

    printf("配列strに文字列\"%s\"が格納されています\n", str);

    return 0;

}
