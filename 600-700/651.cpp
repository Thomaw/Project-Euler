#include <pe.hpp>
const int64 mod = 1000000007;
const int64 mod1 = 1000000006;
int64 comb[50][50];

struct Term {
  // c * x_{v[0]}^{v[1]} * x_{v[2]}^{v[3]} ...
  int64 c;
  vector<int64> v;
};

vector<Term> make_idx_poly(int64 n) {
  vector<Term> target;
  for (auto d : get_factors(n)) {
    target.pb({cal_phi(n / d), {n / d, d}});
  }
  if (n & 1) {
    target.pb({n, {2, n / 2, 1, 1}});
  } else {
    target.pb({n / 2, {2, n / 2}});
    target.pb({n / 2, {2, n / 2 - 1, 1, 2}});
  }
  return target;
}

int64 make_idx(int64 a, int64 x, int64 b, int64 y) {
  // t_a^x t_b^y
  int64 u = gcd(a, b) % mod1;
  return u * x % mod1 * y % mod1;
}

int64 make_idx(const vector<int64>& u, const vector<int64>& v) {
  const int64 n1 = sz(u), n2 = sz(v);
  int64 ret = 0;
  for (int i = 0; i < n1; i += 2)
    for (int j = 0; j < n2; j += 2) {
      ret += make_idx(u[i], u[i + 1], v[j], v[j + 1]);
    }
  return ret % mod1;
}

int64 solve_impl(int64 a, int64 b, int64 m) {
  vector<Term> A = make_idx_poly(a), B = make_idx_poly(b);
  int64 ret = 0;
  for (auto& i1 : A)
    for (auto& i2 : B) {
      int64 c = i1.c * i2.c % mod;
      ret += c * power_mod_ex(m, make_idx(i1.v, i2.v), mod) % mod;
      if (ret >= mod) ret -= mod;
    }
  return ret % mod * inv_of(4 * a % mod * b, mod) % mod;
}

int64 solve(int64 m, int64 a, int64 b) {
  int64 dp[50] = {0, 1};
  for (int64 i = 2; i <= m; ++i) {
    dp[i] = solve_impl(a, b, i);
    for (int64 j = 1; j < i; ++j) {
      dp[i] = sub_mod(dp[i], comb[i][j] * dp[j] % mod, mod);
    }
  }
  return dp[m];
}

int main() {
  pe().maxPrime(2000000).calPhi(1).init();
  init_comb(comb, 49, mod);
  int64 F[50];
  F[0] = 0;
  F[1] = 1;
  for (int i = 2; i < 50; ++i) F[i] = F[i - 1] + F[i - 2];
  int64 ans = 0;
  for (int64 i = 4; i <= 40; ++i) {
    ans += solve(i, F[i - 1], F[i]);
  }
  dbg(ans % mod);
  return 0;
}