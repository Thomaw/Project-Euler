#include <pe.hpp>
const int64 mod = 1000000000;
int64 dp[46368+1];
int64 f[100];
int main() {
  INIT_MAXP(1000000);
  init_primes();
  dp[0] = 1;
  for (int i = 0; ;++i) {
    const int p = plist[i];
    if (p > 46368) break;
    for (int j = 0; j + p <= 46368; ++j) {
      dp[j+p] += dp[j] * p % mod;
      dp[j+p] %= mod;
    }
  }
  f[1] = f[2] = 1;
  for (int i = 3; i <= 24; ++i)
    f[i] = f[i-1] + f[i-2];
  int64 ans = 0;
  for (int i = 2; i <= 24; ++i)
    ans += dp[f[i]];
  dbg(ans%mod);
  return 0;
}