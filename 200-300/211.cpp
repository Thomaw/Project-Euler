
#include <stdio.h>
#include <stdlib.h>

int isSquare(unsigned long long int n)
{
  unsigned long long int x;

  x = sqrt(n);
  return x*x == n;
}

int main(void)
{
  unsigned long long int i, i2, j, counter, bound;
  unsigned long long int *sumDivs2;

  bound = 64000000;
  sumDivs2 = (unsigned long long int*) malloc(bound * sizeof(bound));
  for (i=1; i < bound; i++){
    sumDivs2[i] = 0;
  }

  for (i=1; i < bound; i++){
    i2 = i*i;
    j = i;
    while (j < bound){
      sumDivs2[j] += i2;
      j += i;
    }
  }

  counter = 0;
  for (i=1; i < bound; i++){
    if (isSquare(sumDivs2[i])){
      counter += i;
    }
  }
  printf("Solution: ");printint64(counter);printf("\n");

  return 0;
}