#include <pe.hpp>

DVA<int64> dva(1);

int64 dfs(int limit, int64 n, int64 val, int imp, int64 vmp, int64 now) {
  int64 ret = 0;
  {
    int64 remain = n / val;
    if (remain > vmp) {
      ret += now * (dva[remain] - (imp + 1)) * 2;
    }
    ret += now * 2;
  }
  for (int i = 0; i < limit; ++i) {
    const int64 p = plist[i];
    const int nextimp = imp == -1 ? i : imp;
    const int64 nextvmp = imp == -1 ? p : vmp;
    const int64 valLimit = n / p / nextvmp;
    if (val > valLimit) break;
    for (int64 nextval = val * p, t = now * 2;; t *= 2) {
      ret += dfs(i, n, nextval, nextimp, nextvmp, t);
      if (nextval > valLimit) break;
      nextval *= p;
    }
  }
  return ret;
}

int main() {
  pe().maxPrime(20000000).init();
  const int64 n = 1e14;
  dva = prime_s0_parallel<int64>(n);
  dbg("ok");
  auto ans = dfs(pcnt, n, 1, -1, -1, 1);
  dbg(ans-1);
  return 0;
}