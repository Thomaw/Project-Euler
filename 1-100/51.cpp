const int sz = 1000000;
int nonprime[sz];

int main(int argc, char *argv[]) {
  // Step one: fill the nonprime array by sieve
  // This is where most of the time is spent.
  nonprime[0] = nonprime[1] = 1;
  for (int fill = 4; fill < sz; fill += 2) {
    nonprime[fill] = true;
  }
  for (int p = 3; p * p < sz; p += 2) {
    if (nonprime[p] == false) {
      for (int fill = p * p; fill < sz; fill += p + p) {
        nonprime[fill] = true;
      }
    }
  }
  // Step two: find the best changeling prime
  // Each digit is 0-9; 10 means "*"
  int bestprimes = 0, bestprime = 0;
  for (int a = 0; a <= 10; ++a) {
    for (int b = 0; b <= 10; ++b) {
      for (int c = 0; c <= 10; ++c) {
        for (int d = 0; d <= 10; ++d) {
          for (int e = 0; e <= 10; ++e) {
            // f increments by 2 since even numbers aren't prime.  11 means "*"
            for (int f = 1; f <= 11; f += 2) {
              if (f == 11) f = 10;
              int p = ((a%10)*100000 + (b%10)*10000 + (c%10)*1000 + (d%10)*100 + (e%10)*10 + (f%10));
              int m = ((a/10)*100000 + (b/10)*10000 + (c/10)*1000 + (d/10)*100 + (e/10)*10 + (f/10));
              if (m == 0) continue;
              // our array is nonprime, not prime, so instead of adding, we subtract.
              int primes = 10 - nonprime[p];
              primes -= nonprime[p + m*1]; primes -= nonprime[p + m*2]; primes -= nonprime[p + m*3];
              primes -= nonprime[p + m*4]; primes -= nonprime[p + m*5]; primes -= nonprime[p + m*6];
              primes -= nonprime[p + m*7]; primes -= nonprime[p + m*8]; primes -= nonprime[p + m*9];
              if (primes > bestprimes || primes == 8) {
                // The problem doesn't state it, but numbers of the form *123456 aren't
                // allowed if zero is one of the solutions for *.  We can check for that
                // simply by testing if the mask is greater than p.  And we check for zero
                // as a solution by testing the primality of p + mask * 0, that is, p.
                if (!nonprime[p] && p < m) continue;
                bestprimes = primes;
                bestprime  = p;
                printf("%d is the best so far with %d primes (mask %d)\n", p, primes, m);
                for (int x = 0; x <= 9; ++x) {
                  int pr = p + m * x; 
                  if (!nonprime[pr]) printf("%d\n", pr);
                }
              }
              if (nonprime[p]) continue;
            }
          }
        }
      }
    }
  }
}
