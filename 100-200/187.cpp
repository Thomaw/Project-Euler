#include <stdio.h>
#include <stdlib.h>

#define LIMIT  100000000
#define LIMIT2 50000000

long int find(long int *vs, long int i1, long int i2, double v)
{
  long int im;
  while(i2 - i1 > 1){
    im = (long int)( (i1 + i2) / 2);
    if(vs[im] > v){
      i2 = im;
    }
    else{
      i1 = im;
    }
  }
  return i1;
}


int main(void)
{
  long int i, j, nbPrimes;
  long int* pr = (long int*)malloc(LIMIT2 * sizeof(long int));
  long int* primes;
  long int solution;

  for (i = 0; i < LIMIT2; i++) pr[i] = 1;
  pr[0] = pr[1] = 0;
  for (i = 0; i < LIMIT2/2 + 1; i++){
    if (pr[i]){
      j = i + i;
      while (j < LIMIT2){
        pr[j] = 0;
        j += i;
      }
    }
  }
  nbPrimes = 0;
  for (i = 0; i < LIMIT2; i++) if (pr[i]) nbPrimes++;
  primes = (long int*)malloc(nbPrimes * sizeof(long int));
  j = 0;
  for (i = 0; i < LIMIT2; i++){
    if (pr[i]) primes[j++] = i;
  }
  i = 0;
  solution = 0;
  while(primes[i] * primes[i] < LIMIT){
    solution += find(primes, 0, nbPrimes, (double)LIMIT/primes[i]) + 1 - i;
    i++;
  }
  printf("\n%ld", solution);
  return 0;
}