#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std ;
typedef long long ll ;
typedef vector<ll> po ;
ll MOD = 1000000000 ;
int ps(ll i) {
   ll r = sqrt(i) ;
   return i == r * r ;
}
void shift(int m, po &b) {
   if (m < 0)
      for (int i=0; i<b.size(); i++)
         b[i] = - b[i] ;
   b.insert(b.begin(), 0) ;
}
void add(const po &a, po &b) {
   if (b.size() < a.size())
      b.resize(a.size()) ;
   for (int i=0; i<a.size(); i++)
      b[i] = (b[i] + a[i] + MOD) % MOD ;
}
po sum({1,-1}) ;
int goodpointer = 0 ;
int main(int argc, char *argv[]) {
   int n = atol(argv[1]) ;
   po po2({0,1}) ;
   po po1({1,-1}) ;
   ll r = 0 ;
   for (ll i=3; ; i++) {
      po s ;
      if (!ps(i-2)) {
         po t = po2 ;
         shift(-1, t) ;
         add(po2, s) ;
         add(t, s) ;
      }
      if (!ps(i-1)) {
         po t = po1 ;
         shift(1, t) ;
         add(t, s) ;
      }
      if (ps(i-1)) {
         add(s, sum) ;
         r = (r + sum[goodpointer]) % MOD ;
         cout << "At " << goodpointer << " have " << sum[goodpointer] << " sum " << r << endl << flush ;
         goodpointer++ ;
         if (goodpointer > n)
            exit(0) ;
      }
      if (s.size() > n+1)
         s.resize(n+1) ;
      swap(po1, po2) ;
      swap(po1, s) ;
   }
}