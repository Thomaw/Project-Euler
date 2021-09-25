#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std ;
typedef long long ll ;
/* prime sieve */
const ll MOD = 1000000007 ;
vector<ll> sf ;
ll HI ;
ll s = 0 ;
vector<int> primes ;
vector<ll> cnt ;
ll choose(ll a, ll b) {
   if (b < 0 || b > a)
      return 0 ;
   if (b + b > a)
      b = a - b ;
   ll r = 1 ;
   for (ll i=1; i<=b; i++)
      r = r * (a - i + 1) / i ;
   return r ;
}
void recur(ll prod, int at, int n) {
   if (prod > HI)
      return ;
   while (cnt.size() <= n)
      cnt.push_back(0) ;
   cnt[n] += HI * HI / (prod*prod) ;
   while (at < primes.size() && prod * primes[at] < HI) {
      recur(prod*primes[at], at+1, n+1) ;
      at++ ;
   }
}
int main(int argc, char *argv[]) {
   HI = atoll(argv[1]) ;
   sf.resize(HI+1) ;
   sf[1] = 1 ;
   primes.push_back(2) ;
   for (ll i=2; i<=HI; i += 2)
      sf[i] = 2 ;
   ll primecount = 1 ;
   for (ll i=3; i<=HI; i += 2)
      if (sf[i] == 0) {
         primecount++ ;
         primes.push_back(i) ;
         sf[i] = i ;
         if (HI / i >= i)
            for (ll j=i*i; j<=HI; j += 2*i)
               if (sf[j] == 0)
                  sf[j] = i ;
      }
   recur(1, 0, 0) ;
   for (int i=cnt.size()-1; i>0; i--) {
      for (int j=0; j<i; j++)
         cnt[j] -= cnt[i] * choose(i, j) ;
   }
   for (int i=0; i<cnt.size(); i++)
      cout << i << " " << cnt[i] << endl ;
   ll pp = 1 ;
   for (int i=0; i<cnt.size(); i++)
      pp = (pp * (cnt[i] % MOD)) % MOD ;
   cout << pp << endl ;
}