int main(int argc, char *argv[]) {
  int limit = (argc != 2) ? 1001 : atoi(argv[1]);
  sieve();  // fills the primes array with numprimes primes.
  double min = 10000;
  int minn = 1;
  for (int p1i = 1; p1i < numprimes; ++p1i) {
    unsigned int p1 = primes[p1i];
    if (p1 * (p1 / 10) > limit) {
      printf("Stopping because %d^2 is %d\n", p1, p1 * p1);
      break;
    }
    for (int p2i = p1i - 1; p2i >= 0; --p2i) {
      unsigned int p2 = primes[p2i];
      if ((p1 + p2) % 9 != 1) continue;
      unsigned int n = p1 * p2;
      if (n > limit) continue;
      unsigned int phi = n - p1 - p2 + 1;
      if (double(n) / phi < min) {
        // New low.  Check to be sure phi is a permutation of n:
        char buf1[32], buf2[32];
        sprintf(buf1, "%d", n);
        sprintf(buf2, "%d", phi);
        if (strlen(buf1) != strlen(buf2)) continue;
        std::sort(&buf1[0], &buf1[strlen(buf1)]);
        std::sort(&buf2[0], &buf2[strlen(buf2)]);
        if (strcmp(buf1, buf2) != 0) continue;
        min = double(n) / phi;
        minn = n;
        printf("New min at n=%9d, phi(n)=%9d: %f (n=%d*%d)\n", int(n), phi, min, p1, p2);
      }
    }
  }
}
