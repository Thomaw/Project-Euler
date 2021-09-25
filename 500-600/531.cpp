
const int maxp = 1005000;
#include <pe>

int main()
{
  init_primes(1, 1);
  int64 ans = 0;
  for (int n = 1000000; n < 1005000; ++n)
    for (int m = n + 1; m < 1005000; ++m)
    {
      int64 u, v;
      if (crt2(phi[n], n, phi[m], m, v, u) == 0) continue;
      ans += v;
    }
  dbg(ans);
  return 0;
}