#include <stdio.h>

int main()
{
	int n = 100;
	int *p;

	p = &n;
	
	// &n = p;
	// *&n = 

	printf("int      n : %d\n", n);
	printf("int     *p : %d\n", *p); // == n
	printf("pointa  &n : %p\n", &n); // p

	printf("int    *&n : %d\n", *&n); // *(&n = p) 
	printf("pointa &*p : %p\n", &*p);

	printf("Size of int  n : %u\n", (unsigned int)sizeof(n));
	printf("Size of int *p : %u\n", (unsigned int)sizeof(p));

	printf("Size of int *&n : %u\n", (unsigned int)sizeof(*&n));
	printf("Size of int &*p : %u\n", (unsigned int)sizeof(&*p));


	return 0;
}
