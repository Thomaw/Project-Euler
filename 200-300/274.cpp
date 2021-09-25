#include <stdio.h>
#include <memory.h>

#define N 10000000

static unsigned char primes[N];

void sieve()
{
    memset(primes, 1, sizeof primes);
    primes[0] = primes[1] = 0;
    for (int i = 2; i * i < N; i++) {
        for (int j = i * i; j < N; j += i) primes[j] = 0;
    }
}

int main(int argc, char **argv)
{
    int mult[] = { 0, 9, 0, 3, 0, 0, 0, 7, 0, 1 };
    __int64 a = 0;
    sieve();

    for (int i = 0; i < N; i++) {
        if (i != 2 && i != 5 && primes[i]) {
            a += mult[i % 10] * i + 1;
        }
    }
    printf("sum=%I64d\n", a / 10);
}