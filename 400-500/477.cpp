#include<bits/stdc++.h>
#define MAXN 100000000
#define MODP 1000000007LL
using namespace std;
typedef long long int ll;
typedef unsigned long long int ul;

int main(int argc, char* argv[]) {
  ll s = 0;
  ll *ss = new ll[MAXN];
  ll *sums = new ll[MAXN+1];
  sums[0] = 0;
  map<ll, int> values;
  int period = -1, start_period = 0;
  for (int i = 0; i < MAXN; ++i) {
    ss[i] = s;
    sums[i+1] = s + sums[i];
    if (period < 0 && values.find(s) != values.end()) {
      period = i - values[s];
      start_period = values[s];
    }
    else if (period < 0) values[s] = i;
    s = (s * s + 45LL) % MODP;
  }
  start_period = 2 * (2 + start_period / 2);
  ll k = (MAXN - start_period) / period;
  start_period = MAXN - period * k;
  int n = start_period + period;
  ll* vs = new ll[n];
  ll v1 = 0;
  for (int i = 0; i < n; ++i) vs[i] = ss[i];
  for (int k = 1; k < n; ++k) {
    if (k == start_period) v1 = vs[0];
    for (int i = 0; i+k < n; ++i) {
      int j = i + k;
      ll br1 = ss[j] + sums[j] - sums[i] - vs[i];
      ll br2 = ss[i] + sums[j+1] - sums[i+1] - vs[i+1];
      vs[i] = max(br1, br2);
    }
  }
  ll v2 = vs[0];
  printf("%lli\n", v1 + k * (v2 - v1));
  return 0;
}