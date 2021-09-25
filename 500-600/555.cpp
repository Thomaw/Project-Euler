// Compile: c99 -O3 -Wall -pedantic pe555.c -o re555
// Answer: 208517717451208352 (0.011512 sec, 99th to solve)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_M 1000000

unsigned long answer, d, k;

int main() {
  clock_t start= clock();

  for (d= 1; d <= MAX_M - 1; d++) {
    k= d * 2;
    while ( k <= MAX_M ) {
      answer+= (((MAX_M - k + d) * 2 + d + 1) * d) / 2;
      k+= d;
    }
  }

  double time_count = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf("\n\ne555: %lu\n\n", answer);
  printf("Elapsed time %f seconds\n", time_count);

  return 0;
}