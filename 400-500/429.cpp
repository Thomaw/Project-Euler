#include <iostream>
#include <bitset>

using namespace std;

__int64 PowMod( __int64 base, __int64 exp, __int64 mod )
{
    __int64 ans = 1;
    while ( exp ) {
        if ( exp & 1 ) {
            ans = ans * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return ans;
}

int main()
{
    const __int64 N = 100000000, M = 1000000009;
    static bitset<N+1> isPrime;
    isPrime.set();
    __int64 ans = 1;
    for ( int i = 2; i <= N; i++ ) {
        if ( isPrime[i] ) {
            for ( __int64 j = i; j <= N; j+=i ) {
                isPrime[j] = 0;
            }
            __int64 s = 0;
            for ( __int64 p = i; p <= N; p*=i ) {
                s += N/p;
            }
            ans = ans * (1+PowMod(i,2*s,M)) % M;
        }
    }
    cout << ans << endl;
    return 0;
}