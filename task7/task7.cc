#include <stdio.h>
#include <math.h>
#define I 2

int main ()
{
	int n = 0;
	int *b = &n;

	int const err = scanf("%d",b);

	if ((err != 1) || (*b < 0)) 
	{
		printf("scanf failed %d",err);
		return -1;
	}

	int sqr_n = pow(I,*b);

	printf("%d \n", sqr_n);
	return 0;	
}
