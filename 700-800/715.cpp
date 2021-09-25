
#include <pe.hpp>

const int64 mod = 1000000007;
using MT = NMod64<mod>;

vector<DVA<MT>> pre;
DVA<int64> s3(1);

struct Solver : public MValueBaseTP<Solver, MT, 14> {
  MT batch(int64 n, int64 val, int /*imp*/, int64 vmp, int emp, MT now) {
    MT ret = 0;
    int64 remain = n / val;
    if (remain > vmp) {
      MT tmp = s3[remain] - s3[vmp];
      tmp -= pre[1][remain] - pre[1][vmp];
      tmp += pre[3][remain] - pre[3][vmp];
      ret += tmp * now;
    }
    if (val > 1) {
      ret += now * magic[tid()] * each(vmp, emp + 1);
    } else {
      ret += 1;
    }
    return ret;
  }
  MT each(int64 p, int e) {
    if (p == 2) {
      return power_mod(2, 3 * e, mod);
    } else {
      MT a = power_mod(p % mod, 3 * e, mod);
      MT b = power_mod(p % mod, 3 * e - 3, mod);
      return p % 4 == 1 ? a - b : a + b;
    }
  }
  void visitMaxPrime(int64 /*vmp*/, int /*emp*/, MT now) {
    magic[tid()] = inv_of(now.value(), mod);
  }
  int64 magic[32];
};
Solver solver;
int main() {
  pe().maxPrime(2000000).init();
  const int64 n = 1000000000000;
  pre = prime_s0_pmod<MT>(n, 4);
  s3 = prime_sk_ex<mod>(n, 3);
  cout << solver.solve(n) << endl;
  return 0;
}Mint C(int n, int m) {
    vector<Mint> p2(n + m + 1);
    p2[0] = 1;
    for (int i = 1; i < (int)p2.size(); ++i) {
        p2[i] = p2[i - 1] * 2;
    }
    Mint ans = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            ans += p2[n - i + m - j - 2] * i * j * 4 * 2;
        }
    }
    ans += p2[n + m] - p2[n] * 2 - p2[m] * 2 + 4;
    ans += (p2[n] * 2 + p2[m] * 2 - 4) * n * m;
    ans -= 2 * (n - 1) * (m - 1);
    return ans;
}