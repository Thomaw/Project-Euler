#include <stdio.h>
#include <string.h>
#include "gmp.h"

int main(void)
{

    mpz_t y;
    mpz_t z;
    unsigned long x;
    char buf[3072];    // the result is 3001 characters
    char *pa;

    mpz_init(y);
    mpz_init(z);

    for (x = 1; x <= 1000; x++)
    {
        mpz_ui_pow_ui(y, x, x);
        mpz_add(z, z, y);
    }

    mpz_get_str(buf, 10, z);
    pa = buf + strlen(buf) - 10;
    printf("Answer = %s\n", pa);

    mpz_clear (y);
    mpz_clear (z);

    return 0;
}
