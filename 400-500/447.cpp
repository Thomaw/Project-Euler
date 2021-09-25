#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define ll long long
#define alok(n,t) (t*)malloc((n)*sizeof(t))
#define mod 1000000007

// calculates sum(i) for 1<=i<=n, modulo 10^9+7
// the magic number is 1/2 mod 10^9+7
ll S(ll n) {
    n %= mod;
    return n * (n + 1) % mod * 500000004 % mod;
}

// some formulas used to calculate F(N) = sum(1<=i<=n) R(i):
// F(N) = F(N-1) + sigma'(N)
// F(N) = S(N) - sum(gF(N/g^2))
// sigma'(N) = sum(d|N, (d,N/d)=1) d
// S(N) = S(N-1) + sigma(N)
// S(N) = sum(g*floor(N/g))
// sigma(N) = sum(d|N) d

int main(int argc, char **argv) {
    double tt = clock();
    ll n = argc <= 1 ? 100000000000000LL : atoll(argv[1]);

    // some useful values
    ll s = (ll)sqrt(n);
    ll ns = n / s;
    ll ss = (ll)sqrt(s) + 1;
    ll ct = (ll)pow(n, 2./7);
    ll nk = n / ct / ct;

    // allocate and initialize two arrays, one for small k and
    // one for n/k^2 for small k
    int us = ns > nk ? ns : nk;
    int qs = ss > ct ? ss : ct;
    // we're using these two arrays for different purposes, so
    // the size should be the maximum we need for each purpose
    ll *F  = alok(us + 1, ll);
    ll *Fq = alok(qs + 1, ll);
    for (int i = 0; i <= ns; i++) F [i] = 1;
    for (int i = 0; i <= ss; i++) Fq[i] = 1;

    // first part: 
    // F[i] will contain G(i), for i <= n^(1/2), and 
    // Fq[i] will contain G(n/i^2), for i <= n^(1/4)
    
    // sieve div-sum for small values ...
    // O(n^(1/2) log log n) runtime
    for (ll i = 2; i <= ns; i++) {
        if (F[i] == 1) {
            for (ll pi = i, npi = pi + 1; pi <= ns; pi *= i, npi = npi * i + 1) {
                for (ll j = pi, q = 1; j <= ns; j += pi, q++) {
                    if (q == i) q = 0; else F[j] *= npi;
                }
            }
        }
        F[i] += F[i - 1];
        F[i] %= mod;
    }

    // use S(N) = sum(g*floor(N/g)) for large values, splitting the sum into two
    // parts for an O(N^(1/2)) runtime for each N
    // O(n^(1/2)) runtime
    for (ll v = ss; v; v--) {
        ll i = n / (v * v);
        if (i <= ns) continue;
        ll j = s / v + 1;
        ll ij = i / j;
        ll w = 0;
        for (ll g = 1; g <= ij; g++) {
            w += i % g;
        }
        w %= mod;
        w = i % mod * ij - w;
        for (ll k = 1; k < j; k++) {
            w += S(i / k);
        }
        w %= mod;
        w += (1 - j) * S(ij);
        Fq[v] = w % mod;
    }

    // after the first part, we will reuse the arrays to store F(n).
    // luckily, we will only need S(n) to calculate F(n), so we can
    // replace each value immediately.

    // F[i] will contain F(i), for i <= n^(3/7), and
    // Fq[i] will contain F(n/i^2), for i <= n^(2/7)

    // for small values, sieve. 
    // O(n^(3/7) log log n) runtime
    for (int i = 1; i <= nk; i++) F[i] = 1;
    *F = 0;

    for (ll p = 2; p <= nk; p++) {
        if (F[p] == 1) {
            for (ll pp = p, wp = p + 1; pp <= nk; pp *= p, wp = pp + 1) {
                for (ll j = pp, q = 1; j <= nk; j += pp, q++) {
                    if (q == p) q = 0; else F[j] *= wp;
                }
            }
        }
        F[p] += F[p - 1];
        F[p] %= mod;
    }

    // use F(N) = S(N) - sum(gF(N/g^2)) for large values, splitting the sum
    // into parts for an O(N^(1/3)) runtime for each N
    // O(n^(3/7)) runtime
    for (ll v = ct; v; v--) {
        ll i = n / (v * v);
        if (i <= nk) continue;
        ll w = 0;
        ll j = (ll)pow(i, 1./3) + 1;
        ll ij = i / j, g;
        ll sij = (ll)sqrt(ij);
        for (g = 2; g <= sij; g++) {
            ll igg = i / (g * g);
            if (igg <= nk) break;
            w += g * Fq[v * g];
            w %= mod;
        }
        for (; g <= sij; g++) {
            ll igg = i / (g * g);
            w += g * F[igg];
            w %= mod;
        }
        for (ll k = 1; k < j; k++) {
            w += S((ll)sqrt(i / k)) * (F[k] - F[k - 1]);
            w %= mod;
        }
        w -= S(sij) * F[j - 1];
        if (i <= ns) {
            w = F[i] - w;
        } else {
            w = Fq[v] - w;
        }
        Fq[v] = w % mod;
    }

    // subtract n(n+1)/2
    ll ans = (Fq[1] - S(n)) % mod;

    // adjust mod and print answer    
    if (ans < 0) ans += mod;
    printf("%lld %lld %.3lf s.\n", n, ans, (clock() - tt) / CLOCKS_PER_SEC);
}