#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
int main() {
	unsigned long long int i, k;
	mpz_t a, b, c, d, e, sum;
	int n;
	mpz_init(a);
	mpz_init(b);
	mpz_init(c);
	mpz_init(d);
	mpz_init(e);
	mpz_init(sum);
	k = 987654321;

	// For n = 1 
	mpz_set_ui(a,1);
	mpz_set_ui(b,2);
	mpz_set_ui(c,4);
	for (i=2; i<=k; i++) {
		mpz_set(d,a);
		mpz_set(a,b);
		mpz_set(b,c);
		mpz_mul_ui(c,c,2);
		mpz_sub(c,c,d);
		if (i%2) mpz_add_ui(c,c,1);
		else mpz_sub_ui(c,c,1);
		mpz_mod_ui(c,c,100000000);
	}
	mpz_add(sum, sum, a);

	// For n = 2
	mpz_set_ui(a,223);
	mpz_set_ui(b,863);
	mpz_set_ui(c,3339);
	for (i=5; i<=k; i++) {
		mpz_set(d,a);
		mpz_set(a,b);
		mpz_set(b,c);
		mpz_mul_ui(c,c,4);
		mpz_mul_ui(d,d,2);
		mpz_sub(c,c,d);
		mpz_add_ui(c,c,1);
		mpz_mod_ui(c,c,100000000);
	}
	mpz_add(sum, sum, a);

	mpz_set_ui(e,4);
	for (n=3; n<=30; n++) {
		mpz_mul_ui(e,e,2);
		mpz_mod_ui(e,e,100000000);
		mpz_set_ui(a,0);
		mpz_sub_ui(a,a,1);
		mpz_set_ui(b,2);
		mpz_sub_ui(c,e,1);
		for (i=0; i<=k; i++) {
			mpz_set(d,a);
			mpz_set(a,b);
			mpz_set(b,c);
			mpz_add_ui(c,c,1);
			mpz_mul(c,c,e);
			mpz_add_ui(d,d,1);
			mpz_mul_ui(d,d,n);
			mpz_sub(c,c,d);
			mpz_sub_ui(c,c,1);
			mpz_mod_ui(c,c,100000000);
		}
		mpz_add(sum, sum, a);
	}
	printf("Sum: ");
	mpz_out_str(stdout, 10, sum);
	printf("\n");
	return 0;
}