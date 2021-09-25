#include <bits/stdc++.h>
#include "pe/modulo.h"
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef vector<bool> vb;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)

const ll M = 300000;

int main() {
	vb pr(M,true);
	vl p = {0};
	FOR(i,2,M) if (pr[i]) {
		p.push_back(i);
		for (ll j = i*i; j < M; j += i) pr[j] = false;
	}
	ll N = p.size();
	set<ll> s;
	vl a(N,1), q(N,1);
	FOR(n,2,N) {
		FOR(m,n,N) if (!a[m]) s.insert(p[m]);
		FOR(m,n,N) q[m] = q[m]*p[n-1] % p[m];

		ll k = (n-a[n]) * modInv(q[n],p[n]) % p[n];
		if (k < 0) k += p[n];
		
		FOR(m,n+1,N) a[m] = (a[m] + k*q[m]) % p[m];
	}
	
	ll res = 0;
	for (ll x: s) res += x;
	cout << res << endl;
}