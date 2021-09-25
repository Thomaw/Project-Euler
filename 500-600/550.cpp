#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;
#define sz(c) ll((c).size())
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
#define pb push_back
#define has(c,i) ((c).find(i) != end(c))

const ll G = 64, MOD = 987654321;

vl operator*(const vl &a, const vl &b) {
	vl c(G);
	FOR(i,0,G) FOR(j,0,G) c[i^j] = (c[i^j] + a[i]*b[j]) % MOD;
	return c;
}

vl power(vl a, ll n) {
	vl res(G);
	res[0] = 1;
	while (n) {
		if (n & 1) res = res*a;
		a = a*a;
		n /= 2;
	}
	return res;
}


int main() {
	ll n = 1e7 + 1;
	
	vvl d(n);
	FOR(i,2,n) for (ll j = i+i; j < n; j += i) d[j].pb(i);

	vl g(n);
	FOR(i,2,n) {
		set<ll> s;
		FOR(j,0,sz(d[i])) FOR(k,j,sz(d[i])) s.insert(g[d[i][j]] ^ g[d[i][k]]);
		while (has(s,g[i])) g[i]++;
	}
	
	vl a(G);
	FOR(i,2,n) a[g[i]]++;

	a = power(a,1e12);

	ll res = 0;
	FOR(i,1,G) res = (res + a[i]) % MOD;
	cout << res << endl;	
}