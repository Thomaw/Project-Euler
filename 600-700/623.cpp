#include<bits/stdc++.h>
using namespace std;

const int MAXN = 4e3;
const int MAXV = 4e3;

typedef long long ll;

const ll MOD = ll(1e9 + 7);

ll dp[MAXN][MAXV];

// returns number of length exactly N with V variables in scope
ll lambda(int N, int V=0) {
	assert(N);
	assert(N > 0);
	assert(V >= 0);
	if (N == 1) return V;
	if (dp[N][V]) return dp[N][V];
	ll &res = dp[N][V];
	// Abstraction
	if (N > 5) {
		res += lambda(N-5, V+1);
	}
	if (N >= 4) {
		for (int i = 1; i < N-2; i++) {
			res += lambda(i, V) * lambda(N-2-i, V);
			res %= MOD;
		}
	}
	return res;
}

ll LAMBDA(int N) {
	ll res = 0;
	for (int i = 1; i <= N; i++) {
		res += lambda(i);
	}
	return res % MOD;
}

int main() {
	assert(LAMBDA(6) == 1);
	assert(LAMBDA(9) == 2);
	assert(LAMBDA(15) == 20);
	assert(LAMBDA(35) == 3166438);
	cout << LAMBDA(2000) << '\n';
	return 0;
}