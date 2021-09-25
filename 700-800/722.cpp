int main() {
  double f = 0, s = 0, t = 1; unsigned i, j;
  for (i = 1; i < 8; i++, f += t, t = 1)
    for (j = 0; j < 16; j++, t /= i);
  for (i = 1; i < 16; i++) f *= i;
  for (j = 1; j <= 2; j++, s += t, t = 1./j)
    for (i = 0; i < 25 * j; i++) t /= 2;
  for (i = 0; i < 16; i++) f /= s;
  int printf(const char *, ...); printf("%.12e\n", f);
}