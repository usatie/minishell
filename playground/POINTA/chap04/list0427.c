#include <stdio.h>
#include <string.h>

int main(void)
{
    char s1[10], s2[10], s3[10];
    char *x = "XXXXXXXXX";

    strcpy(s1, "ABC");
    printf("s1 = %s\n", s1);

    printf("s1 = %s\n", strcpy(s1, "1234"));

    strcpy(s2, strcpy(s1, "HAL"));
    printf("s1 = %s\n", s1);
    printf("s2 = %s\n", s2);

    strcpy(s3, x); strncpy(s3, "12345", 3);      printf("s3 = %s\n", s3);
    strcpy(s3, x); strncpy(s3, "12345", 5);      printf("s3 = %s\n", s3);
    strcpy(s3, x); strncpy(s3, "12345", 7);      printf("s3 = %s\n", s3);
    strcpy(s3, x); strncpy(s3, "1234567890", 9); printf("s3 = %s\n", s3);

    return 0;
}
