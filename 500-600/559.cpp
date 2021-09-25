#include "library/trivial.h"
#include "library/util.h"
#include "library/int-mod.h"

const int MOD = 1000000123;
typedef int_mod<MOD> im;

const int N = 50000;
im fac[N+1];
im facr[N+1];

im dp[N+1];

im P(int k) {
	dp[0] = fastpow(fac[N], N);
	for (int t = k; t <= N; t = max(t+1, min(t+k, N))) {
		dp[t] = 0;
		for (int h = 0; h <= t; h = max(h+1, min(h+k, t)))
			dp[t] -= dp[h]*facr[t-h];
	}
	return (1-(N+k-1)/k%2*2)*dp[N];
}

int main() {
	fac[0] = 1;
	REP(n,1,N+1) {
		fac[n] = n*fac[n-1];
		facr[n] = fastpow(fastpow(fac[n], MOD-2), N);
	}
	im res = 0;
	REP(k,1,N+1)
		res += P(k);
	printf("%lld\n", res.v);
	return 0;
}