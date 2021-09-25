#include<bits/stdc++.h>
using namespace std;

typedef long double ld;

ld F(int N) {

	ld res = N;

	for(int t = N; t > 0; t--) {

		// expected value of ith highest is i * exp
		ld exp = N + 1;	
		exp /= t + 1;

		ld cutoff = floor(res / exp);
		assert(cutoff * exp <= res);
		assert((cutoff + 1) * exp > res);
		assert(cutoff <= t);

		res = ((t - cutoff) * res + (cutoff) * (cutoff + 1) / 2 * exp) / t;
	}

	return res;
}

int main() {
	cout << fixed << setprecision(10) << F(1000000) << '\n';
}