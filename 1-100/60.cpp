const int sz = 6550;  // goes up to prime 65,609
int prime[sz];  // the nth prime, where prime 0 is 2
char pairs[sz][sz]; // can the xth prime be concat'd with the yth prime?

// Test for primality, blindly assuming the prime[] array is big enough.
// It's slow to do all these divides, but faster than doing a sieve up to a billion :-)
bool isprime(unsigned int n) {
  if (n == 2) return true;
  for (int i = 0; ; ++i) {
    int p = prime[i];
    if (p * p > n) return true;
    if (n / p * p == n) return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  int limit = (argc != 2) ? 999999 : atoi(argv[1]);
  int *filler = &amp;prime[0];
  // Step one: fill the prime[] array
  *filler++ = 2;
  *filler++ = 3;
  for (int p = 5; ; p += 2) {
    if (isprime(p)) {
      *filler++ = p;
      if (filler == &amp;prime[sz]) break;
    }
  }
  // Step two: find concatenatable primes
  int sum = 0;
  int ashift = 10;
  for (int ai = 0; ai < sz; ++ai) {
    int a = prime[ai];
    if (a > ashift) ashift *= 10;
    int bshift = 10;
    // two-part loop.  Part one fills in a little more of the pairs[] array.
    for (int bi = 0; bi < ai; ++bi) {
      int b = prime[bi];
      if (b > bshift) bshift *= 10;
      if (isprime(a * bshift + b) && isprime(b * ashift + a)) {
        // Note that we always index pairs with the highest number first
        pairs[ai][bi] = true;
      }
    }
    // In part two, we check for five concatenatable primes.
    for (int bi = 0; bi < ai; ++bi) {
      if (!pairs[ai][bi]) continue;
      for (int ci = 0; ci < bi; ++ci) {
        if (!pairs[ai][ci] || !pairs[bi][ci]) continue;
        for (int di = 0; di < ci; ++di) {
          if (!pairs[ai][di] || !pairs[bi][di] || !pairs[ci][di]) continue;
          for (int ei = 0; ei < di; ++ei) {
            if (!pairs[ai][ei] || !pairs[bi][ei] || !pairs[ci][ei] || !pairs[di][ei]) continue;
            printf("%d, %d, %d, %d, and %d are concatenatable\n",
                   prime[ai], prime[bi], prime[ci], prime[di], prime[ei]);
            printf("And their sum is %d\n",
                   prime[ai] + prime[bi] + prime[ci] + prime[di] + prime[ei]);
            if (--limit == 0) return 0;
          }
        }
      }
    }
  }
}
