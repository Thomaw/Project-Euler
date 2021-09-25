#include <stdio.h>   
#include <stdlib.h>  
#include <gmp.h>
#include <pthread.h>

void printn(mpz_t n) {
  while(1) {
    gmp_printf("At: %Zd\r", n); fflush(stdout); sleep(1);
  }
}

int main() {
  pthread_t thread;
  pthread_attr_t thread_attr;
  mpz_t n, n2;
  unsigned long result = 0;

  pthread_attr_init(&thread_attr);
  pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
  
  mpz_init2(n, 1L);
  mpz_init(n2);

  pthread_create(&thread, &thread_attr, (void *(*)(void *)) printn, n);

  while(mpz_cmp_ui(n, 50000000L)<=0) {
    mpz_pow_ui(n2, n, 2UL);
    mpz_mul_ui(n2, n2, 2UL);
    mpz_sub_ui(n2, n2, 1UL);
    if(mpz_probab_prime_p(n2,5)>0) {
      result++;
    }
    mpz_add_ui(n, n, 1);
  }
  printf("\n\nResult: %ul\n", result);
  return 0;
}