#include <stdio.h>
#include <math.h>

int main() {

	unsigned long long int x, h,t,p;

	for (h = 145;  ; h++) {
		x = h * ( 2 * h - 1);
		t = ( sqrt(8* x + 1) - 1) / 2 ;
		p = ( sqrt(24 * x + 1) + 1) / 6 ;

		if ((t * (t+1)/2) == (p * (3 * p - 1) / 2))
			break;
	}
	return printf("%llu\n" ,  x );
}
