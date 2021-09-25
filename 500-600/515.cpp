#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

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

bool Miller_Rabin(ll p, int it) {
    if (p < 2) {
        return false;
    }
    if (p != 2 && p % 2 == 0) {
        return false;
    }
    ll s = p - 1;
    while (s % 2 == 0) {
        s /= 2;
    }
    for (int i = 0; i < it; i++) {
        ll a = rand() % (p - 1) + 1;
        ll temp = s;
        ll mod = modpow(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1) {
            mod = ((mod % p) * (mod % p)) % p;
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    ll a = 1000000000LL;
    ll b = 100000LL;
    ll k = 100000LL;
    int c = 0;
    k--;
    ll sum = 0LL;
    for (ll p = a + 1LL; p <= a + b; p += 2) {
        if (Miller_Rabin(p, 5)) {
            c++;
            ll temp = modInverse(k, p);
            sum += temp;
        }
    }
    printf("D(%lld, %lld, %lld) = %lld\n", a, b, (k + 1), sum);
    printf("No. of primes in the range is %d\n", c);
    cout << "Time elapsed : " << (1.0 * clock() / CLOCKS_PER_SEC) << " seconds" << endl;);
    return 0;
}