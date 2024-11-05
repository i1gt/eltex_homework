#include <stdio.h>
#define i 2

int main ()
{
	int N, sqrN = i;
	scanf("%d", &N);
	for (int s = 2; N>=s; N = N-1, sqrN = sqrN*i){}
	printf("%d \n", sqrN);
	return 0;	
}
