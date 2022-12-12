#include <stdio.h>
#include <string.h>

int main(void)
{
    char    str[128];
    char    tmp[128];
    int     ch;
    char    *p;

    printf("文字列を入力してください:");
    scanf("%s", str);

    printf("探す文字は:");
    scanf("%s", tmp);
    ch = tmp[0];

    if ((p = strchr(str, ch)) == NULL)
        printf("文字'%c'は文字列中に存在しません\n", ch);
    else {
        printf("文字'%c'の最初の出現以降は\"%s\"です\n", ch, p);
        p = strrchar(str, ch);
        printf("文字'%c'の最初の出現以降は\"%s\"です\n", ch, p);
    }
    return 0;
}
