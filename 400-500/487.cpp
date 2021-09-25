#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

bool isprime(ll a) {
	if(a % 2 == 0) return a == 2;
	for(ll i = 3; i * i <= a; i += 2) if(a % i == 0) return false;
	return true;
}

ll exp(ll a, ll b, ll m) {
	ll r = 1;
	while(b) {
		if(b % 2) r *= a, r %= m;
		a *= a, a %= m;
		b /= 2;
	}
	return r;
}

ll f(ll k, ll n, ll p) {
	if(k % (p - 1) == 0) return n - n / p;
	n %= p;
	if(p - 1 - n < n) return (p - (k % 2 ? -1 : 1) * f(k, p - 1 - n, p)) % p;

	ll res = 0;
	for(ll i = 1; i <= n; i++) {
		res += exp(i, k, p);
		if(res >= p) res -= p;
	}
	return res;
}

ll s(ll k, ll n, ll p) {
	return ((n + 1) % p * f(k, n, p) % p + p - f(k + 1, n, p)) % p;
}

int main() {
	ll res = 0;
	for(ll i = 2e9; i <= 2e9 + 2000; i++) {
		if(isprime(i)) {
			res += s(10000, 1e12, i);
		}
	}
	cout << res << '\n';
	return 0;
}