#include <cstdio>

typedef long long LL;

const int MOD = 1000000000;
// (a + (a+1) + ... + b) % MOD
int sum(LL a, LL b) {
  if(b<a) return 0;
  LL c = a+b;
  LL d = b-a+1;
  if(c%2) d/=2; else c/=2;
  c %= MOD;
  d %= MOD;
  return c * d % MOD;
}

int calc(LL N) {
  N--;
  int res=0;
  for(LL p=4;p<N;p*=2) {
    LL q = p/2;
    LL x = p-1;
    LL k = (N+1-x)/p * p;
    res = (res + (k/2) % MOD * sum(q-1,x-1) + q % MOD * sum(x, x+k-1)) % MOD;
    LL c0 = x + k + q;
    if(c0 > N) continue;
    res = (res + (q % MOD) * ((c0+q-2)%MOD) % MOD * ((N-c0+1)%MOD)) % MOD;
    res = (res + (q % MOD) * sum(c0, N)) % MOD;
  }
  return res;
}

int main()
{
  printf("%d\n",calc(1000000000000000000LL));
  return 0;
}