#include <stdio.h>

int main(void){
	int       nm = 1;
	const int nc = 2;

	int       *       p1;
	const int *       p2;
	int       * const p3m = &nm;
	int       * const p3c = &nc;
	const int * const p4m = &nm;
	const int * const p4c = &nc;

	nm = 100;				
	nc = 100;
	p1 = &nm;	*p1 = 100;
	p1 = &nc;	*p1 = 100;

	p2 = &nm;	*p2 = 100;
	p2 = &nc;	*p2 = 100;

	p3m = &nm;	p3c = &nc;

	*p3m = 100;		
	*p3c = 100;		

	p4m = &nm;	p4c = &nc;	

	*p4m = 100;			
	*p4c = 100;			

	return 0;
}
