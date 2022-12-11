#include <stdio.h>

void str_copy(char d[], const char s[])
{
    int i = 0;
    while ((d[i] = s[i]) != '\0')
        i++;
}

int main(void)
{
    char str[128] = "ABC";
    char tmp[128];

    printf("文字列strは\"%s\"です\n", str);
    printf("コピーする文字列は:");
    scanf("%s", tmp);

    str_copy(str, tmp);

    printf("文字列strは\"%s\"です\n",str);

    return 0;
}
