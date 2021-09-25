#include <math.h>
#include <stdio.h>

static inline int ispow(int i) {

	int x,nc;
	double check ;

	for (nc = 0,x = i ; x > 0 ; x /= 10,nc++)
	;

	le pogledt ce je all good */
	check = pow(i , (1.0 / (double) nc) );
	
	if ( (double)(check - (int)check) <= 0.00000001 || (double)(check - (int)check) >= 0.999999999)
		return 1 ;
		
	return 0;
}

int
main() {

	int j = 1,i;
	for (i = 1; i < 1000000000; i++) 
		if (ispow(i)) 
			j++;

	return printf("%d\n" , j);;
}
