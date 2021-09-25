#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const int MAX = 100000;
const int prime_count = 9592;
const int N = 10010000;
const ll mod = 1000000007LL;

bool isPrime[MAX];
int prime[prime_count], fac[N + 1], invfac[N + 1];

ll modpow(ll a, ll p, ll n) {
    ll r = a % n;
    if (p == 0) {
        return ll(1);
    }
    if (p == 1) {
        return r;
    }
    if (p % 2 == 1) {
        r = modpow(a, p / 2, n) % n;
        r = r * r % n;
        return r * a % n;
    } else {
        r = modpow(a, p / 2, n) % n;
        r = r * r % n;
        return r;
    }
}

ll modInverse(ll a, ll p) {
    return modpow(a, p - 2, p);
}

bool isPrime_large(ll n) {
    for (ll i = 0; prime[i] * prime[i] <= n; i++) {
        if (n % prime[i] == 0) {
            return false;
        }
    }
    return true;
}

ll C(int n, int k) {
    if (k > n) {
        return 0;
    }
    ll res = fac[n];
    res = res * invfac[k] % mod;
    res = res * invfac[n - k] % mod;
    return res;
}

int main() {
    for (int i = 2; i < MAX; i++) {
        if (!isPrime[i]) {
            int j = i + i;
            while (j < MAX) {
                isPrime[j] = true;
                j += i;
            }
        }
    }
    int pi = 0;
    for (int i = 2; i < MAX; i++) {
        if (!isPrime[i]) {
            prime[pi] = i;
            pi++;
        }
    }
    fac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = (int)(ll(fac[i - 1]) * ll(i) % mod);
    }
    for (int i = 0; i <= N; i++) {
        invfac[i] = (int)modInverse((long)fac[i], mod);
    }
    ll res = 0LL;
    for (int p = 10000001; p < 10010000; p += 2) {
        if (isPrime_large(ll(p))) {
            int n = p;
            double a = sqrt((double)n);
            ll sum = 0LL;
            for (int i = 0; i <= (double)n / a; i++) {
                int x = (int)((double)n - (a - 1) * (double)i);
                sum += C(x, i);
                sum %= mod;
            }
            if (sum < 0) {
                sum += mod;
            }
            res += sum;
            res %= mod;
        }
    }
    if (res < 0) {
        res += mod;
    }
    cout << res << endl;
    cout << "Time elapsed : " << (1.0 * clock() / CLOCKS_PER_SEC) << " seconds" << endl;
    return 0;
}