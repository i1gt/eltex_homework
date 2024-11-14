#include <stdio.h>
#include <math.h>
#define i 2

int main ()
{
	int N;
	int *n=&N;
	scanf("%d", n);
	int sqrN = pow (i,*n);
	printf("%d \n", sqrN);
	return 0;	
}
