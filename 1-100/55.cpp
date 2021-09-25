#include <stdio.h>
#include <gmp.h>

void Invert(mpz_t *inverted, mpz_t number) {
  mpz_t num;
  mpz_t temp;
  mpz_init_set_ui(temp, 0);
  mpz_init_set_ui(*inverted,0);
  mpz_init_set(num, number);

  while (mpz_cmp_ui(num,0)) {
    mpz_mul_ui(*inverted, *inverted, 10);
    mpz_mod_ui(temp, num, 10);
    mpz_div_ui(num, num,10);
    mpz_add(*inverted, *inverted, temp);
  }
  mpz_clear(num);
  mpz_clear(temp);
}

int main() {
  int i = 0;
  int j = 0;
  unsigned long count = 0;
  int ok = 0;
  mpz_t num;
  mpz_t inv;
  mpz_init_set_ui(inv, 0);
  mpz_init_set_ui(num, 0);

  for (i = 1; i < 10000; ++i) {
    mpz_set_ui(num, i);
    ok = 0;
    for (j = 0; j < 50; ++j) {
      Invert(&inv, num);
      mpz_add(num, num, inv);
      Invert(&inv, num);
      if (mpz_cmp(inv,num) == 0) {
        ok = 1;
        break;
      }
    }
    if (!ok) ++count;
  }
  printf("%d\n",count);
  mpz_clear(num);
  mpz_clear(inv);
}
