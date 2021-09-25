#include <stdio.h>
#include "cworld/PrimesTo.h"

long *pr;
long N;
long total = 11;

/******************************************************************

Let S(n) be the sum of all positive integers m not exceeding n having the following property:
a^(m+4) = a (mod m) for all integers a.

The values of m <= 100 that satisfy this property are 1, 2, 3, 5 and 21, thus S(100) = 1+2+3+5+21 = 32.
You are given S(10^6) = 22868117.

Find S(10^12).

******************************************************************/

//////////////////////////////////////////////////////////////////
long plist[100];

void deeper(long k, long n, long f) {    // try to add another prime factor to n
  long p, np, flag, x, xp;

  for (  ;  pr[k]!= 0 ;  ++k )  {
      p = pr[k];
      plist[f] = p;
      np = n*p;
      if (np > N) return;
      if (0 == (n+3)%(p-1)) {
        flag = 1;
        for (x=0; x<f; ++x) {
          xp = plist[x];
          if (0 != ((np/xp)+3)%(xp-1)) {
            flag = 0;
            break;
          }
        }
        if (flag) 
          total += np;
      }
      deeper(k+1,np,f+1);
    }
}

//////////////////////////////////////////////////////////////////

int main(int argc,  char **argv) {
  long k;


  pr = PrimesTo(1000000);     // list of primes is terminated with a 0

  if (1<argc)  N = strtol(argv[1],NULL,10);
  else         N = 1000000;
  
  total = 11;


  for (k=1; pr[k]<N && pr[k]<2000; ++k) {
    plist[0] = pr[k];                       // plist is list of prime factors of current n in deeper()
    deeper(k+1,pr[k],1);
  }

  printf("total = %ld\n",total);
}