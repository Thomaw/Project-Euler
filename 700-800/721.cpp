#define P 999999937
void mult(unsigned long x[2], unsigned long y[2], unsigned a, unsigned long z[2]) {
  unsigned t[2] = {(((x[0]*y[0])%P + ((x[1]*y[1])%P)*a)%P)%P,
    ((x[0]*y[1])%P + (x[1]*y[0])%P)%P};
  z[0] = t[0], z[1] = t[1];
}
void pomod(unsigned long x[2], unsigned a, unsigned long n, unsigned long r[2]) {
  r[0] = 1, r[1] = 0;
  while (n) {
    if (n & 1) mult(r, x, a, r);
    n >>= 1;
    mult(x, x, a, x);
  }
}
unsigned long rt(unsigned long n) {
  unsigned long r = 0, b = 1ul << 30;
  while (b > n) b >>= 2;
  while (b) {
    if (n >= r + b) {
      n -= r + b;
      r = (r >> 1) + b;
    } else r >>= 1;
    b >>= 2;
  }
  return r;
}
unsigned h(unsigned long a) {
  unsigned long r = rt(a), x[2] = {r,1}, y[2];
  if (r * r != a) x[0]++;
  pomod(x, a, a*a, y);
  return y[0];
}
int printf(const char *, ...);
int main() {
  unsigned n = 5000000, r = 1;
  for (unsigned a = 2; a <= n; a++) r = (r + h(a)) % P;
  printf("%lu\n", (2 * r + P - n + rt(n))%P);
}