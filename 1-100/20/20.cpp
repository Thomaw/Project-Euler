#include <gmp.h>
#include <stdio.h>

int main() {

	mpz_t rez,nm;
	mpz_init(rez);
	mpz_init(nm);
	
	mpz_set_ui(rez, 1);
	unsigned long i;
	
	for (i = 2 ; i <= 100; i++) 
		mpz_mul_ui(rez, rez,i);

	
	
	i = 0;
	mpz_set(nm,rez);
	while (mpz_sgn(nm)) {
		i += mpz_mod_ui(rez, nm , 10);
		mpz_fdiv_q_ui(nm , nm , 10);
	}	


	printf("%lu\n" , i);
}
