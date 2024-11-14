#include <stdio.h>
#define I 2

int main ()
{
	int n; 
	int sqr_n = I;

	int const err = scanf("%d", &n);
	if ((err != 1) || (n < 0)) 
	{
		printf("scanf failed %d",err);
		return -1;
	}

	for (int s = 2; n >= s; --n)
	{
		sqr_n = sqr_n*I;
	}
	printf("%d \n", sqr_n);
	return 0;	
}
