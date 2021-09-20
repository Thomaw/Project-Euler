#include <gmp.h>
#include <stdio.h>

int main() {

	mpz_t nm,rez ;
	mpz_init (nm);
	mpz_init(rez);
	unsigned long i = 0;
	
	mpz_ui_pow_ui(nm , 2 , 1000);

	while (mpz_sgn(nm)) {
		i += mpz_mod_ui(rez, nm , 10);
		mpz_fdiv_q_ui(nm , nm , 10);
	}	
	
	return printf("%lu\n" , i);
	
}
