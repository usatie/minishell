#include <stdio.h>

char *weekstr(int wd)
{
    static char wstr[][10] = {"Sundat","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    return (wd >= 0 && wd < 7) ? wstr[wd] : NULL;
}



int main(void)
{
    int n;
    int retry;

    puts("曜日を表す英単語を表示します!");

    do {
        printf("0-日曜日/1-月曜日/.../6-土曜日:");
            scanf("%d", &n);

            if (n >= 0 && n < 7)
                printf("英語では%sです\n", weekstr(n));
        
            printf("もう一度？ 0-いいえ/1-はい:");
            scanf("%d", &retry);
    } while (retry == 1);

    return 0;
}
