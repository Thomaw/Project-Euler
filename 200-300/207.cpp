#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "string.h"


int main(void)
{
	long a = 1, b = 1, j = 2, k = 0, m = 2, o = 4;
	for(;;)
	{
		k++;
		if(k == j)
		{
			a++;
			j *= 2;
			k = 0;
		}
		b++;
		
		m += o;
		o += 2;
		
		if(12345*a < b) break;
	}
	
	printf("%li, %li -> %li\n", a, b, m);
	
	return 0;
}
