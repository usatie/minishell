# include <stdio.h>

int main(void){
    int n1 = 15;
    int n2 = 73;

    printf("n1の値 = %d\n", n1);
    printf("n2の値 = %d\n", n2);


    printf("n1のアドレス = %p\n", &n1);
    printf("n2のアドレス = %p\n", &n2);

    return (0);
}