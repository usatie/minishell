#include <stdio.h>
#include <string.h>

int main(void)
{
    char st[128];

    puts("\"ABCDE\"との比較を行います");
    puts("\"XXXXX\"で終了します");

    while(1){
        printf("\n文字列st:");
        scanf("%s", st);

        if (strcmp(st, "XXXXX") == 0)
            break;
        printf("strcmp( \"ABCDE\",st)        = %d\n", strcmp("ABCDE", st));
        printf("strncmp( \"ABCDE\", st, 3)   = %d\n", strncmp("ABCDE", st, 3));
    }
    return 0;
}
