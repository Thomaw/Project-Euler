#include <pe.hpp>
const int64 mod = 1000000007;

int main() {
  pe().maxPrime(2000000).calMu().calPhi().init();
  MuPhiSumModer ct(mod, maxp);
  const int64 n = 100000000000;
  int64 ans = 0;
  for (int k = 1; 1LL << k <= n; ++k) {
    const int64 m = n / (1LL << k);
    int64 last = 0;
    for (int64 d = 1; d <= m;){
      int128 v = m / d;
      int64 maxd = m / v;
      if (maxd > m) maxd = m;
      int64 curr = ct.get_sum_mu(maxd);
      int64 delta = sub_mod(curr, last, mod);
      ans += (v *(v-1)/2 %mod) * delta % mod;
      d = maxd + 1;
      last = curr;
    }
  }
  dbg(ans%mod);
  return 0;
}