#include <stdio.h>

void fill(int *a, int n1, int n2, int v)
{
    int i, j;

    for (i = 0; i < n1; i++)
        for (j = 0; j < n2; j++)
            a[i * n2 + j] = v;
}

int main(void)
{
    int i, j, no;

    int x[3][2];
    int y[4][3];

    printf("全構成要素に代入する値:");
    scanf("%d", &no);

    fill(&x[0][0], 3, 2, no);
    fill(&y[0][0], 4, 3, no);

    puts("--- x ---");
    for (i = 0; i < 3; i++){
        for (j = 0; j < 2; j++)
            printf("%3d", x[i][j]);
        putchar('\n');
    }
    puts("--- y ---");
    for (i = 0; i < 4; i++){
        for (j = 0; j < 3; j++)
            printf("%3d", y[i][j]);
        putchar('\n');
    }

    return 0;
}
