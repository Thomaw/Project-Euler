
#include <stdio.h>

typedef long long int ll;

int main() {
  ll f(ll n, ll m) {
    ll ans=0, i=1, tri=1, q=n; // q=n/i in the Boolean expressions
    for(ll old=n%m, qmod; i<q; old=qmod, i++, tri+=i, tri%=m) {
      q=n/(i+1); qmod=q%m;
      ans += ((old - qmod) * tri + (old * (old + 1) / 2)) % m;
    }
    if (i==q) ans+=tri;
    return ans%m;
  }
  ll r=100000000, m=1000000007;
  ll tmp=(1 + 8 * (f(r*r, m) - 4 * f(r*r/4, m))) % m;
  printf("%lld\n", (tmp>=0)?tmp:tmp+m);
}