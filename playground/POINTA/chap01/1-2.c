#include <stdio.h>

int main()
{
	int n;
	int *p;

	printf("sizeof*p           : %lu\n", sizeof*p);  // *p no size
	printf("sizeof&n           : %lu\n", sizeof&n);　// 
	printf("sizeof-1           : %lu\n", sizeof-1);
	printf("sizeof(unsigned)-1 : %lu\n", sizeof(unsigned)-1); // unsigned no bite size -1
	printf("sizeof(double)     : %lu\n", sizeof(double)-1);   // double no bite size -1
	printf("sizeof((double)-1) : %lu\n", sizeof((double)-1)); //
	printf("sizeof n+2         : %lu\n", sizeof n+2);           //
	printf("sizeof(n+2)        : %lu\n", sizeof(n+2));         //
	printf("sizeof(n+2.0)      : %lu\n", sizeof(n+2.0));       //



	return 0;
}
