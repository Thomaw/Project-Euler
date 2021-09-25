
#include <cstdio>
#include <cmath>

#include <iostream>
#include <functional>

int main() {
  using i64 = long long;

  const i64 N = 1e13;
  constexpr int v = sqrt(N);
  static i64 larges[v + 1];
  static int smalls[v + 1], primes[v + 1];

  for (int i = 1; i <= v; ++i) smalls[i] = i - 1, larges[i] = N / i - 1;
  for (int p = 2; p <= v; ++p) if (smalls[p] > smalls[p - 1]) {
    int pcnt = smalls[p - 1];
    i64 q = i64(p) * p;
    for (int i = 1; i <= std::min(i64(v), N / q); ++i) {
      i64 d = i64(i) * p;
      larges[i] -= ((d <= v) ? larges[d] : smalls[N / d]) - pcnt;
    }
    for (int i = v; i >= q; --i) smalls[i] -= smalls[i / p] - pcnt;
  }
  int prime_count = 0;
  for (int i = 2; i <= v; ++i) if (smalls[i] > smalls[i - 1]) {
    primes[prime_count++] = i;
  }
  primes[prime_count++] = v + 1;

  std::function< i64(i64, int, int) > rec = [&] (i64 m, int pi, int lim) {
    i64 ret = ((m > v) ? larges[N / m] : smalls[m]) - pi;
    for (int pj = pi; pj < prime_count; ++pj) {
      int p = primes[pj], e = 1;
      i64 nm = m / p;
      if (nm < p) break;
      for (; nm >= p; nm /= p, ret += 1, e += 1) {
        ret += rec(nm, pj + 1, e);
        if (e == lim) break;
      }
    }
    return ret;
  };
  printf("%lld\n", rec(N, 0, 64) + 1);
  return 0;
}