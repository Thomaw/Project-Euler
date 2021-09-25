#include <iostream>
using namespace std ;
using ll = long long ;
int main(int argc, char *argv[]) {
   ll inc = 1504170715041707L ;
   ll mod = 4503599627370517L ;
   ll lo = inc ;
   ll hi = inc ;
   ll s = lo ;
   while (lo > 0) {
      ll next = (lo + hi) % mod ;
      if (next < lo) {
         lo = next ;
         s += lo ;
      } else {
         hi = next ;
      }
   }
   cout << s << endl ;
}