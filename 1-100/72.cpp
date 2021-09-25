#define limit 1000000
// return the number of reduced fractions between two other
// reduced fractions, given only their denominators.
uint64_t count(int d1, int d2) {
  int dx = d1 + d2;
  if (dx > limit) return 0;
  return 1 + count(d1, dx) + count(d2, dx);
}

int main(int argc, char *argv[]) {
  uint64_t counts = 1 + 2 * count(1, 2);
  printf("Fractions from 0/1 to 1/1, denom limited to %d, number %q\n", limit, counts);
}
