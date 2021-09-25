
const int maxp = 2000000;
#include <pe>

const int64 mod = 1000000000+7;

const int F = 200;
const int64 N = 1000000000000;
const int64 sqrtN = sqrt(N);

int L;
int L1;

int64 invs[1000000 + 100];

int pp[F+1];
int pp2[F+1];

static_assert(sqrtN*sqrtN == N);

int64 ans;

int64 scon[1000000+10];
int64 lcon[1000000+10];

const int TC = 30;
int64 sdata[TC][1000000+10];
int64 ldata[TC][1000000+10];

void dfs0(int limit, int64 value, int64 x, int64* scon, int64* lcon, int id)
{
  if (value > 1 || value == 1 && id == 0)
  {
    int64 t = N / value;
    if (value <= t)
    {
      scon[value] = add_mod(scon[value], x, mod);
    }
    else
    {
      lcon[t] = add_mod(lcon[t], x, mod);
    }
  }
  for (int i = L; i < limit; ++i)
  {
    if (value == 1) if (i % TC != id) continue;
    const int64 p = plist[i];
    int c = 1;
    int64 v = p;
    if (p > N / value) break;
    while (v <= N / value)
    {
      dfs0(i, v * value, x * (c+1) % mod, scon, lcon, id);
      if (v > N / value / p)
      {
        break;
      }
      v *= p;
      ++c;
    }
  }
}

void dfs1(int limit, int64 value, int64 x)
{
  {
    int64 other = N / value;
    if (other <= sqrtN)
    {
      ans = add_mod(ans, scon[other] * x % mod, mod);
    }
    else
    {
      ans = add_mod(ans, lcon[N/other] * x % mod, mod);
    }
  }
  for (int i = 0; i < limit; ++i)
  {
    if (value == 1) dbg(i);
    const int64 p = plist[i];
    int c = 1;
    int64 v = p;
    if (p > N / value) break;
    while (v <= N / value)
    {
      int64 a = pp[p];
      int64 b = a + c + 1;
      b = b * (b + 1) / 2 % mod;
      int64 bb = c;
      bb = bb * (bb + 1) / 2 % mod;
      b = sub_mod(b, bb, mod);
      dfs1(i, v * value, x * invs[pp2[p]] % mod * b % mod);
      if (v > N / value / p)
      {
        break;
      }
      v *= p;
      ++c;
    }
  }
}

int main()
{
  init_primes();
  init_inv(invs, 1000000, mod);
  
  vector<int64> scnt;
  vector<int64> lcnt;
  tie(scnt, lcnt) = prime_pi(N);

  while (plist[L] <= F) ++L;
  while (plist[L1] <= sqrtN) ++L1;
  {
   BEGIN_PARALLEL
      FROM 0 TO TC-1 EACH_BLOCK_IS 1 CACHE ""
      THREADS TC
      MAP
        {
          dfs0(L1, 1, 1, sdata[key], ldata[key], key);
        }
      REDUCE
        {
          return 0;
        }
    END_PARALLEL;
    for (int i = 0; i < TC; ++i)
      for (int j = 0; j <= sqrtN; ++j)
        scon[j] = add_mod(scon[j], sdata[i][j], mod),
        lcon[j] = add_mod(lcon[j], ldata[i][j], mod);
  }
  {
    for (int i = 2; i <= sqrtN; ++i)
    {
      scon[i] = add_mod(scon[i], scon[i-1], mod);
    }
    lcon[sqrtN] = scon[sqrtN];
    for (int i = sqrtN - 1; i >= 1; --i)
    {
      lcon[i] = add_mod(lcon[i], lcon[i+1], mod);
    }
    for (int64 i = 1; i < sqrtN; ++i)
    for (int64 j = 1; j * sqrtN < N / i; ++j)
    {
      int64 cnt = lcnt[i*j];
      cnt = sub_mod(cnt%mod, scnt[sqrtN]%mod, mod);
      cnt = cnt * 2 % mod;
      int64 t = cnt * sub_mod(scon[j], scon[j-1], mod) % mod;
      lcon[i] = add_mod(lcon[i], t, mod);
    }
  }
  int64 value = 1;
  for (int i = 0; i < L; ++i)
  {
    int64 total = 0;
    for (int64 j = plist[i]; j <= F; j *= plist[i])
    {
      total += F / j;
    }
    pp[plist[i]] = total;
    pp2[plist[i]] = (total + 1 + 1) * (total + 1) / 2;
    value = value * pp2[plist[i]] % mod;
  }
  dfs1(L, 1, value);
  dbg(ans);
  return 0;
}



Update:
@hk Rating removed.

Update 07/03/2017:
Instead of a hacky approach as I mentioned above, I found that it is pretty easy to obtain an approach without advanced analysis skills.
Replace d by k1 and replace k by k2, D(m,n)=∑k1|m∑nk2σ0(k1k2). Since each factor of ab can be written in the form of pbq where p|a and q|b, we have
